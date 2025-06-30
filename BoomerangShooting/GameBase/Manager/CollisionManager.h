#pragma once
//#include "GameBase/Component/Components.h"

class ColliderComponent;

class CollisionManager
{

public:
	//コンストラクタ
	CollisionManager();
	//デストラクタ
	~CollisionManager();
	//更新処理
	void Update(const float& deltaTime);

	//コライダーの追加
	void AddCollider(ColliderComponent* collider);
	//コライダーの削除
	void RemoveCollider(ColliderComponent* collider);

private:

	//移動オブジェクト同士
	void Collision_Collision(ColliderComponent* collider1, ColliderComponent* collider2);
	//固定オブジェクト同士
	void Fixed_Fixed(ColliderComponent* collider1, ColliderComponent* collider2);
	//すり抜けオブジェクト同士
	void Trigger_Trigger(ColliderComponent* collider1, ColliderComponent* collider2);
	//固定オブジェクトと移動オブジェクト
	void Fixed_Collision(ColliderComponent* collider1, ColliderComponent* collider2);
	//固定オブジェクトすり抜けオブジェクト
	void Fixed_Trigger(ColliderComponent* collider1, ColliderComponent* collider2);
	//移動オブジェクトとすり抜けオブジェクト
	void Collision_Trigger(ColliderComponent* collider1, ColliderComponent* collider2);

	//通知を送る
	void SendNotification(ColliderComponent* collider1, ColliderComponent* collider2,bool isHit);

private:

	std::vector<ColliderComponent*> m_colliderList;

};