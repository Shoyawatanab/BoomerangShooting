#pragma once
#include "GameBase/Actor.h"

class Camera;

class Explosiion : public Actor
{
public:
	// アニメーションサイズ
	static constexpr float ANIMATION_SIZE = 1.0f / 7.0f;	// 7枚
	// アニメーションのインターバル：フレーム単位
	static constexpr int ANIMATION_INTERVAL = 5;
	//初期の大きさ
	static constexpr DirectX::SimpleMath::Vector2 SCALE {5, 5};


public:
	//コンストラク
	Explosiion(Scene* scene);
	//デストラクタ
	~Explosiion() override;

	// コンポーネント全体の更新
	void UpdateActor(const float& deltaTime) override;

	//描画処理
	void Render(const Camera& camera);

	//アクティブになった時に呼ばれる関数
	void OnEnable() override;


private:

	// ポリゴン描画用
// ポリゴン
	DirectX::VertexPositionTexture m_vertices[4];
	// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// ビルボード行列
	DirectX::SimpleMath::Matrix m_billboardMat;

	// フレームカウンタ
	int m_frameCounter;
	// アニメーションキー
	int m_animationKey;


};
