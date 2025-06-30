#pragma once
#include "GameBase/Component/Components.h"

class Camera;

class RenderManager
{
	
public:

	//コンストラクタ
	RenderManager();
	//デストラクタ
	~RenderManager();

	//描画処理
	void Render(const Camera& camera);
	//モデルの追加
	void AddModel(ModelComponent* comp);
	//モデルの削除
	void RemoveModel(ModelComponent* comp);
	//UIの追加
	void AddUserInterface(ImageComponent* comp);
	//UIの削除
	void RemoveUserInterface(ImageComponent* comp);

	//コライダーの追加　デバッグ　
	void AddCollider(ColliderComponent* comp);

	//エフェクトの追加
	void AddEffect(EffectComponent* comp);
	//丸影の追加
	void AddRoundShadow(RoundShadowComponent* comp);


private:
	//モデルコンポーネント
	std::vector<ModelComponent*> m_models;
	//UIコンポーネント
	std::vector<ImageComponent*> m_uis;
	//エフェクトコンポーネント
	std::vector<EffectComponent*> m_effects;
	//丸影
	std::vector<RoundShadowComponent*> m_roundShadow;

	//デバッグ　
	//当たり判定
	std::vector<ColliderComponent*> m_colliders;
	//ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;
	//プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

	

};