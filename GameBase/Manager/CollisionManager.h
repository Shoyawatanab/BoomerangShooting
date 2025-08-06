/*
	クラス名     : CollisionManager
	説明         : 当たり判定マネージャー
	補足・注意点 : Sceneで宣言
*/
#pragma once
#include "GameBase/Actor.h"
#include <unordered_map>

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


	//Rayとの当たり判定
	void RayCollision(DirectX::SimpleMath::Ray ray, float maxLength, Actor::ObjectTag tag, DirectX::SimpleMath::Vector3* pushBack);


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

private:

	//通知を送る
	void SendNotification(ColliderComponent* collider1, ColliderComponent* collider2,bool isHit);

private:
	//コライダーリスト
	std::vector<ColliderComponent*> m_colliderList;

	//オブジェクトタグごとのリスト
	std::unordered_map<Actor::ObjectTag, std::vector<ColliderComponent*>> m_objectTagList;



};