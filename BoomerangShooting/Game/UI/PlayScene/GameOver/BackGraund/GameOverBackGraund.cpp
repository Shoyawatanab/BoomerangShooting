#include "pch.h"
#include "GameOverBackGraund.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/GameResources.h"
#include "GameBase/Common/Commons.h"
///	<summary>
///	インプットレイアウト
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> GameOverBackGraund::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};



/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas"></param>
GameOverBackGraund::GameOverBackGraund(Canvas* canvas)
	:
	Image(canvas,"ClearBackGraund")
	,m_time{}
{
	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	//シェーダーの作成
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	CreateShader(device, context);

	LoadTexture();

	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);

	auto comp = GetComponent<ImageComponent>();

	comp->SetCustomRenderFunction(std::bind(& GameOverBackGraund::CustomRender, this));

}

/// <summary>
/// デストラクタ
/// </summary>
GameOverBackGraund::~GameOverBackGraund()
{
}

/// <summary>
/// 単体更新
/// </summary>
/// <param name="deltaTime">経過時間</param>
void GameOverBackGraund::UpdateActor(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	m_time += deltaTime;

	m_time = std::min(m_time, ANIMATION_TIME);

	if (m_time == ANIMATION_TIME)
	{

		for (auto& actor : m_actor)
		{
			if (!actor->GetActive())
			{
				actor->SetActive(true);
			}
		}

	}

}

/// <summary>
/// アクティブ状態になった時
/// </summary>
void GameOverBackGraund::OnEnable()
{
	m_time = 0.0f;
}

/// <summary>
/// 描画
/// </summary>
void GameOverBackGraund::CustomRender()
{

	//シェーダーの作成
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();


	//頂点情報(板ポリゴンの４頂点の座標情報）
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(0.0f,  0.0f, 0.0f), DirectX::SimpleMath::Vector4::One, DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matProj = DirectX::SimpleMath::Matrix::Identity;
	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity;
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.time = DirectX::SimpleMath::Vector4(m_time, ANIMATION_TIME, 1, 1);

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
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//	カリングは左周り
	context->RSSetState(states->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	//インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

void GameOverBackGraund::CreateShader(ID3D11Device1* device, ID3D11DeviceContext* context)
{

	auto shaderFactory = ShaderFactory::GetInstance();
	//各シェーダーの作成
	m_vertexShader = shaderFactory->CreateVS(device, "GameOverVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "GameOverPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "GameOverGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "GameOverVS.cso");

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
/// 画像の読み込み
/// </summary>
void GameOverBackGraund::LoadTexture()
{
	//画像の読み込み
	m_texture = GameResources::GetInstance()->GetTexture("GameOver");

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
	//m_textureWidth = desc.Width;
	//m_textureHeight = desc.Height;

}

