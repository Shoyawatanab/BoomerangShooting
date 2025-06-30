#include "pch.h"
#include "PlayerDamageEffect.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "Game/Messenger/Scene/SceneMessages.h"

///	<summary>
///	インプットレイアウト
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> PlayerDamageEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene"></param>
PlayerDamageEffect::PlayerDamageEffect(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_alpha{1.0f}
	,m_image{}
{

	//コンテキストの取得
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();


	m_image = GetScene()->AddActor<Image>(canvas,"HP");
	m_image->SetCustomRenderFunction(std::bind(&PlayerDamageEffect::CustomRender, this));


	CreateShader();

	//	プリミティブバッチの作成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);

	m_image->SetActive(false);

	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_DAMAGE
		}, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerDamageEffect::~PlayerDamageEffect()
{
}

/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime"></param>
void PlayerDamageEffect::UpdateActor(const float& deltaTime)
{
	//透明度の更新
	m_alpha -= deltaTime * 1.0f;

	//透明になったら
	if (m_alpha <= 0)
	{
		m_image->SetActive(false);
	}
}

/// <summary>
/// カスタム描画
/// </summary>
void PlayerDamageEffect::CustomRender()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//コンテキストの取得
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//デバイスの取得
	auto states = CommonResources::GetInstance()->GetCommonStates();


	//	頂点情報(板ポリゴンの４頂点の座標情報）
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(Vector3(0.0f,  0.0f, 0.0f),Vector4::One,Vector2(0.0f, 0.0f)),
	};

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = Matrix::Identity;
	cbuff.matProj = Matrix::Identity;
	cbuff.matWorld = Matrix::Identity;
	cbuff.Diffuse = Vector4(1, 1, 1, 1);
	cbuff.Time = Vector4(m_alpha, 0.0f, 0.0f, 0.0f);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
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



	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void PlayerDamageEffect::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{
		case SceneMessageType::PLAYER_DAMAGE:
			Begin();
			break;
		default:
			break;
	}

}

/// <summary>
/// シェーダー作成
/// </summary>
void PlayerDamageEffect::CreateShader()
{
	//シェーダーの作成
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();


	auto shaderFactory = ShaderFactory::GetInstance();


	//各シェーダーの作成
	m_vertexShader = shaderFactory->CreateVS(device, "DamageVignetteVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "DamageVignettePS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "DamageVignetteGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "DamageVignetteVS.cso");

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_cBuffer);

}

/// <summary>
/// 開始
/// </summary>
void PlayerDamageEffect::Begin()
{

	m_image->SetActive(true);
	m_alpha = 1.0f;

}
