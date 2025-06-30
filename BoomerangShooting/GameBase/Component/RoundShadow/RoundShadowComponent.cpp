#include "pch.h"
#include "RoundShadowComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="radius">半径</param>
RoundShadowComponent::RoundShadowComponent(Actor* owner, float radius)
	:
	Component(owner)
	,m_radius{radius}
{
	using namespace DirectX;

	//マネージャーに追加
	GetActor()->GetScene()->GetRenderMangaer()->AddRoundShadow(this);

	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// ベーシックエフェクトを設定する
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(false);
	m_basicEffect->SetTextureEnabled(true);
	m_basicEffect->SetLightingEnabled(false);

	// 入力レイアウトを設定する
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	// プリミティブバッチを生成する
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// 画像を読み込む
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			L"Resources/Textures/Shadow.png",
			nullptr,
			m_texture.ReleaseAndGetAddressOf()
		)
	);

	// 深度ステンシルバッファを設定する
	D3D11_DEPTH_STENCIL_DESC desc{};

	// 影：描画先のステンシルバッファと参照値が同じとき影を描画する
	desc.DepthEnable = true;									// 深度テストを行う
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;			// 深度バッファを更新する
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;				// 深度値以下なら更新する

	desc.StencilEnable = true;									// ステンシルテストを行う
	desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;		// 0xff
	desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;	// 0xff

	// 表面
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;		// 参照値とステンシル値が同値なら
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;		// OK　何もしない
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;		// NG　何もしない
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;	// NG　何もしない

	// 裏面も同じ設定
	desc.BackFace = desc.FrontFace;

	// 深度ステンシルステートを作成する
	device->CreateDepthStencilState(&desc, m_depthStencilState.ReleaseAndGetAddressOf());


}

/// <summary>
/// デストラクタ
/// </summary>
RoundShadowComponent::~RoundShadowComponent()
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void RoundShadowComponent::Render(const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();


	// アルファブレンドを適用する
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);

	// 深度ステンシルステートを適用する
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 1);	// 参照値：1

	// カリングを設定する
	context->RSSetState(states->CullCounterClockwise());

	// テクスチャサンプラを適用する
	ID3D11SamplerState* sampler = { states->LinearClamp() };
	context->PSSetSamplers(0, 1, &sampler);

	// 入力レイアウトを適用する
	context->IASetInputLayout(m_inputLayout.Get());

	// エフェクトを設定し適用する
	m_basicEffect->SetWorld(Matrix::Identity);
	m_basicEffect->SetView(camera.GetViewMatrix());
	m_basicEffect->SetProjection(camera.GetProjectionMatrix());
	m_basicEffect->SetTexture(m_texture.Get());
	m_basicEffect->Apply(context);

	// 影ポリゴンの頂点情報を定義する
	VertexPositionTexture vertices[] = {
		VertexPositionTexture(Vector3::Zero,Vector2(0.0f, 0.0f)),
		VertexPositionTexture(Vector3::Zero,Vector2(1.0f, 0.0f)),
		VertexPositionTexture(Vector3::Zero,Vector2(0.0f, 1.0f)),
		VertexPositionTexture(Vector3::Zero,Vector2(1.0f, 1.0f)),
	};

	// 影ポリゴンのインデックス情報を定義する：DrawIndexedで描画するときに必要
	uint16_t indexes[] = { 0, 1, 2, 1, 3, 2 };

	auto position = GetActor()->GetTransform()->GetWorldPosition();
	//床に合わせる
	position.y = 0.1f;

	// 影ポリゴンの頂点情報を設定する
	vertices[0].position = Vector3(-m_radius, 0.01f, -m_radius) + position;
	vertices[1].position = Vector3(m_radius, 0.01f, -m_radius) + position;
	vertices[2].position = Vector3(-m_radius, 0.01f, m_radius) + position;
	vertices[3].position = Vector3(m_radius, 0.01f, m_radius) + position;

	// 影ポリゴンを描画する
	m_primitiveBatch->Begin();

	// DrawIndexedで描画する
	m_primitiveBatch->DrawIndexed(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indexes,
		_countof(indexes),
		vertices,
		_countof(vertices)
	);


	m_primitiveBatch->End();

}


