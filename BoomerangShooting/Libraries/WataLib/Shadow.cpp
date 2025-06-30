/*
	@file	Shadow.cpp
	@brief	影ポリゴンを表示するクラス
*/
#include "pch.h"
#include "Shadow.h"


/// <summary>
/// コンストラクタ
/// </summary>
WataLib::Shadow::Shadow()
	:
	m_texture{},
	m_primitiveBatch{},
	m_basicEffect{},
	m_inputLayout{},
	m_depthStencilState{}
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="context">コンテキスト</param>
/// <param name="states">コモンステート</param>
void WataLib::Shadow::Initialize(
	ID3D11Device* device,
	ID3D11DeviceContext* context,
	DirectX::CommonStates* states
)
{
	using namespace DirectX;

	assert(device);
	assert(context);
	assert(states);

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
/// 描画
/// </summary>
/// <param name="context">コンテキスト</param>
/// <param name="states">コモンステート</param>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
/// <param name="position">座標</param>
/// <param name="radius">半径</param>
void WataLib::Shadow::Render(
	ID3D11DeviceContext* context,
	DirectX::CommonStates* states,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection,
	const DirectX::SimpleMath::Vector3& position,
	float radius
)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	assert(context);
	assert(states);

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
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(projection);
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

	// 影ポリゴンの頂点情報を設定する
	vertices[0].position = Vector3(-radius, 0.01f, -radius) + position;
	vertices[1].position = Vector3( radius, 0.01f, -radius) + position;
	vertices[2].position = Vector3(-radius, 0.01f,  radius) + position;
	vertices[3].position = Vector3( radius, 0.01f,  radius) + position;

	// 影ポリゴンを描画する
	m_primitiveBatch->Begin();

	// DrawIndexedで描画する①
	m_primitiveBatch->DrawIndexed(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indexes,
		_countof(indexes),
		vertices,
		_countof(vertices)
	);

	//// DrawQuadで描画する②
	//m_primitiveBatch->DrawQuad(vertices[0], vertices[1], vertices[3], vertices[2]);

	m_primitiveBatch->End();
}
