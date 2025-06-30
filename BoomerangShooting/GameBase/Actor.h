#pragma once
#include"Component.h"

class Scene;
class Transform;
class ColliderComponent;

class Actor
{
public:
	//オブジェクトタグ
	enum class ObjectTag
	{
		NONE                               //通常
		,PLAYER							   //プレイヤ
		,PLAYER_PARTS					   //プレイヤパーツ
		,STAGE							   //ステージ
		,BOOMERANG						   //ブーメラン
		,BOSS_ENEMY						   //ボス敵
		,BOSS_ENEMY_PARTS				   //ボス敵パーツ
		,BIRD_ENEMY						   //鳥の敵
		,ENEMY							   //敵
		,BEAM							   //ビーム
		,BIRD_BULLET                       //鳥敵の弾								   
	};

public:
	// シーンのセット
	void SetScene(Scene* scene) { m_scene = scene; }
	//シーンの取得
	Scene* GetScene() const { return m_scene; }
	// トランスフォーム取得
	Transform* GetTransform() const { return m_transform; }
	// アクティブのセット　true: 有効　false:無効
	void SetActive(bool active);
	//アクティブの取得 true: 有効　false:無効
	bool GetActive() const { return m_isActive; }
	// 破壊フラグ取得
	bool GetIsDestroy() const { return m_isDestroy; }
	// コンポ―ネント破壊フラグ
	void ComponentDestroyOn() { m_isComponentDestroy = true; }

	//オブジェクトタグの取得
	virtual ObjectTag GetObjectTag() { return ObjectTag::NONE; }



public:
	// コンストラクタ
	Actor(Scene* scene);
	// デストラクタ
	virtual ~Actor();
	// 初期化
	virtual void Initialize() {};
	// 更新処理
	void Update(const float& deltaTime);
	// コンポーネント全体の更新
	void UpdateComponent(const float& deltaTime);
	// 単体更新
	virtual void UpdateActor(const float& deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };
	// 終了処理
	virtual void Finalize() {};
	//アクティブになった時に呼ばれる関数
	virtual void OnEnable() {};
	//非アクティブになった時に呼ばれる関数
	virtual void OnDisable() {}
	// 削除
	void Destroy();
	// コンポーネント追加
	template<typename Comp , typename ...Args>
	Comp* AddComponent(Args&&...args);
	// コンポーネント取得
	template<typename Comp>
	Comp* GetComponent();
	


//Collision関係
	//当たった時に呼び出される
	virtual void OnCollisionEnter(ColliderComponent* collider) { UNREFERENCED_PARAMETER(collider); };
	//当たり続けているときの呼び出される
	virtual void OnCollisionStay(ColliderComponent* collider) { UNREFERENCED_PARAMETER(collider); };
	//衝突が終了したときに呼び出される
	virtual void OnCollisionExit(ColliderComponent* collider) { UNREFERENCED_PARAMETER(collider); };


private:
	// コンポーネント削除
	void RemoveComponent();

private:
	// 所属シーン
	Scene* m_scene;
	// 管理するコンポーネント
	std::vector<std::unique_ptr<Component>> m_components;
	// トランスフォーム
	Transform* m_transform;
	// アクティブフラグ
	bool m_isActive;
	// 破壊フラグ
	bool m_isDestroy;
	// コンポーネント破壊フラグ
	bool m_isComponentDestroy;

};

template<typename Comp , typename...Args>
inline Comp* Actor::AddComponent(Args&&...args)
{
	// コンポーネントの作成
	auto component = std::make_unique<Comp>(std::forward<Args>(args)...);
	// リターンコンポーネント
	Comp * back = component.get();
	// コンポーネントにプッシュバックする
	m_components.push_back(std::move(component));
	// コンポーネントを返す
	return back;

}

template<typename Comp>
inline Comp* Actor::GetComponent()
{
	// コンポーネントを探す
	for (auto& component : m_components)
	{
		if (typeid(*component) == typeid(Comp))
		{
			Comp* comp = dynamic_cast<Comp*>(component.get());
			return comp;
		}
	}
	return nullptr;
}