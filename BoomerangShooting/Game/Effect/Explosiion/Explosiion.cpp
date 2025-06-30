#include "pch.h"
#include "Explosiion.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
Explosiion::Explosiion(Scene* scene)
	:
	Actor(scene)
	,m_animationKey{}
	,m_basicEffect{}
	,m_billboardMat{}
	,m_frameCounter{}
	,m_inputLayout{}
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	AddComponent<EffectComponent>(this, std::bind(&Explosiion::Render, this, std::placeholders::_1));



	//デバイスの取得
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	//コンテキストの取得
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// ポリゴンを設定する
	// 「m_vertices[i].position」はコンストラクタでゼロ初期化済み
	// ここではUV座標を指定している：初期値
	m_vertices[0].textureCoordinate = Vector2(0.0f, 0.0f);	// 左上
	m_vertices[1].textureCoordinate = Vector2(1.0f, 0.0f);	// 右上
	m_vertices[2].textureCoordinate = Vector2(0.0f, 1.0f);	// 左下
	m_vertices[3].textureCoordinate = Vector2(1.0f, 1.0f);	// 右下

	// ポリゴン描画の準備----------------------------------
	// ベーシックエフェクトを設定する
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetTextureEnabled(true);	// テクスチャを有効化

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
			L"Resources/Textures/Explosion.png",
			nullptr,
			m_texture.ReleaseAndGetAddressOf()
		)
	);

	SetActive(false);

}

Explosiion::~Explosiion()
{
}

/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime">経過時間</param>
void Explosiion::UpdateActor(const float& deltaTime)
{

	// フレームカウンタ
	m_frameCounter++;

	// アニメーションの切り替え判定
	if (m_frameCounter > ANIMATION_INTERVAL)
	{
		m_frameCounter = 0;		// フレームカウンタをリセットする
		m_animationKey++;		// アニメーションのキーを進める

		//アニメーションの終了
		if (m_animationKey >= 10)
		{
			SetActive(false);
			m_animationKey = 0;
		}

	}


}



/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void Explosiion::Render(const Camera& camera)
{

	using namespace DirectX::SimpleMath;

	//コンテキストの取得
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//コモンステートの主特区
	auto states = CommonResources::GetInstance()->GetCommonStates();

	auto view = camera.GetViewMatrix();
	auto prijection = camera.GetProjectionMatrix();

	// ビルボードマトリックスを計算する
	m_billboardMat = view.Invert();
	m_billboardMat._41 = 0.0f;
	m_billboardMat._42 = 0.0f;
	m_billboardMat._43 = 0.0f;



	// ポリゴンを描画する準備------------------------------------
	// デバイスコンテキストのパラメータを変更する
	// アルファブレンドを適用する
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);

	// 描画に深度値を適用する
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	// 裏面カリング（反時計回り面を描画しない）を設定する
	context->RSSetState(states->CullNone());

	// テクスチャサンプラにリニアクランプを適用する
	ID3D11SamplerState* sampler = states->LinearClamp();
	context->PSSetSamplers(0, 1, &sampler);

	// 入力レイアウトを適用する
	context->IASetInputLayout(m_inputLayout.Get());


	// ポリゴンを描画する----------------------------------
	// ポリゴンのパラメータを設定する
	float radius = 0.40f;


	// ポリゴンの頂点情報を設定する：ビルボード行列を使うため、XY平面にしている
	m_vertices[0].position = Vector3(-radius, radius, 0.0f);
	m_vertices[1].position = Vector3(radius, radius, 0.0f);
	m_vertices[2].position = Vector3(-radius, -radius, 0.0f);
	m_vertices[3].position = Vector3(radius, -radius, 0.0f);

	// ポリゴンのUV座標を設定する：アニメーション対応
	m_vertices[0].textureCoordinate = Vector2(ANIMATION_SIZE * m_animationKey, 0.0f);	// 左上
	m_vertices[1].textureCoordinate = Vector2(ANIMATION_SIZE * m_animationKey + ANIMATION_SIZE, 0.0f);	// 右上
	m_vertices[2].textureCoordinate = Vector2(ANIMATION_SIZE * m_animationKey, 1.0f);	// 左下
	m_vertices[3].textureCoordinate = Vector2(ANIMATION_SIZE * m_animationKey + ANIMATION_SIZE, 1.0f);	// 右下

	// ビルボード行列を加味したワールド行列を計算する
	Matrix world;
	world *= Matrix::CreateScale((SCALE * GetTransform()->GetWorldScale()));
	world *= m_billboardMat;
	world *= Matrix::CreateTranslation(GetTransform()->GetWorldPosition());

	// ベーシックエフェクトを設定し適用する
	m_basicEffect->SetWorld(world);	// ワールド行列
	m_basicEffect->SetView(view);				// ビュー行列
	m_basicEffect->SetProjection(prijection);	// 射影行列
	m_basicEffect->SetTexture(m_texture.Get());	// テクスチャ
	m_basicEffect->Apply(context);				// 変更を適用する

	// ポリゴンを描画する
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(m_vertices[0], m_vertices[1], m_vertices[3], m_vertices[2]);
	m_primitiveBatch->End();


}

/// <summary>
/// アクティブ状態になった時
/// </summary>
void Explosiion::OnEnable()
{
	m_frameCounter = 0;
	m_animationKey = 0;
}
