#include "pch.h"
#include "ImageComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/GameResources.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "Libraries/MyLib/BinaryFile.h"
#include "GameBase/Screen.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> ImageComponent::INPUT_LAYOUT =
{
	 { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};




ImageComponent::ImageComponent(Actor* owner, std::string textureName)
	:
	Component(owner)
	,m_texture{}
	,m_CBuffer{}
	,m_inputLayout{}
	, m_vertexShader{}
	,m_pixelShader{}
	,m_geometryShader{}
	,m_textureHeight{}
	,m_textureWidth{}
	,m_color{DirectX::SimpleMath::Vector4(1.0f,1.0f,1.0f,1.0f)}
	,m_cutRange{DirectX::SimpleMath::Vector4(0.0f,0.0f,1.0f,1.0f)}
	,m_viewRange{DirectX::SimpleMath::Vector4::One}
	,m_fillAmount{DirectX::SimpleMath::Vector4::One}
	,m_renderKinds{RenderKinds::NORMAL}
{

	using namespace DirectX;


	//マネージャーに追加
	GetActor()->GetScene()->GetRenderMangaer()->AddUserInterface(this);

	LoadTexture(textureName);


	//シェーダーの作成
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();


	auto shaderFactory = ShaderFactory::GetInstance();

	//各シェーダーの作成
	m_vertexShader = shaderFactory->CreateVS(device, "UIVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "UIPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "UIGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "UIVS.cso");


	//	プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);


	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}

/// <summary>
/// デストラクタ
/// </summary>
ImageComponent::~ImageComponent()
{
}


void ImageComponent::Render()
{

	switch (m_renderKinds)
	{
		case ImageComponent::RenderKinds::NORMAL:
			NormalRender();
			break;
		case ImageComponent::RenderKinds::CUSTOM:
			CustomRender();
			break;
		default:
			break;
	}

}



void ImageComponent::LoadTexture(std::string textureName)
{

	//画像の読み込み
	m_texture = GameResources::GetInstance()->GetTexture(textureName);

	//シェーダーリソースビューから画像情報の取得
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	m_texture->GetResource(&resource);

	//リソースをTexture2Dにキャスト
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(resource.As(&tex));

	//画像情報を取得
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//画像のサイズを取得
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;
}

void ImageComponent::NormalRender()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto states = CommonResources::GetInstance()->GetCommonStates();



	VertexPositionTexture vertex{};

	//シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.windowSize = SimpleMath::Vector4(Screen::WIDTH, Screen::HEIGHT, 0, 0);
	cbuff.Position = Vector4(GetActor()->GetTransform()->GetWorldPosition().x, GetActor()->GetTransform()->GetWorldPosition().y, 0, 0);
	cbuff.Size = Vector4(GetWidth(), GetHeight(), 0, 0);
	cbuff.Color = m_color;
	cbuff.CutRange = m_cutRange;
	cbuff.ViewRange = m_viewRange;
	cbuff.FillAmount = m_fillAmount;

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//	半透明描画指定
	ID3D11BlendState* blendstate = states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(states->DepthNone(), 0);

	context->RSSetState(states->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());


	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());


	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex, 1);
	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

/// <summary>
/// カスタム描画
/// </summary>
void ImageComponent::CustomRender()
{
	m_customRender();
}

/// <summary>
/// 横幅の取得
/// </summary>
/// <returns></returns>
float ImageComponent::GetWidth() const
{
	return m_textureWidth * GetActor()->GetTransform()->GetWorldScale().x;
}

/// <summary>
/// 縦幅の取得
/// </summary>
/// <returns></returns>
float ImageComponent::GetHeight() const
{
	return m_textureHeight * GetActor()->GetTransform()->GetWorldScale().y;
}


/// <summary>
/// カスタム描画関数の登録
/// </summary>
/// <param name="customRender">関数</param>
void ImageComponent::SetCustomRenderFunction(std::function<void()> customRender)
{

	m_customRender = customRender;
	//状態の変更
	m_renderKinds = RenderKinds::CUSTOM;
}
