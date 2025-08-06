/*
	クラス名     : DetectionCollision
	説明         : 当たり判定を行うクラス
	補足・注意点 : 
*/
#pragma once
#include "GameBase/Component/Collider/ColliderComponent.h"

class DetectionCollision
{

public:
	//コンストラクタ
	DetectionCollision() = default;
	//デストラクタ
	~DetectionCollision() = default;
	//当たったかどうかのチェック true : 当たった  false : 当たってない
	static bool ChecOnCollision(ColliderComponent* collider1, ColliderComponent* collier2);
	//押し出し
	static const DirectX::SimpleMath::Vector3 Extrusion(ColliderComponent* collider1, ColliderComponent* collider2);

	//線分との当たり判定
	static DirectX::SimpleMath::Vector3 CheckLineSegmentCollision(DirectX::SimpleMath::Ray ray, float maxLength, ColliderComponent& collider);

private:

//当たっているかの判定関数
	//AABB同士の判定
	static bool AABB_AABB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);
	//OBB同士の判定
	static bool OBB_OBB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);
	//スフィア同士の判定
	static bool SPHERE_SPHERE_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);
	//AABBとOBBの判定
	static bool AABB_OBB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);
	//AABBとスフィアの判定
	static bool AABB_SPHERE_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2);

//押しだしの関数

	//AABB同士の押し出し
	static DirectX::SimpleMath::Vector3 AABB_AABB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);
	//OBB同士の押し出し
	static DirectX::SimpleMath::Vector3 OBB_OBB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);
	//スフィア同士の押し出し
	static DirectX::SimpleMath::Vector3 SPHERE_SPHERE_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);
	//AABBとOBBの押し出し
	static DirectX::SimpleMath::Vector3 AABB_OBB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);
	//AABBとスフィアの押し出し
	static DirectX::SimpleMath::Vector3 AABB_SPHERE_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2);


private:


	//当たり判定のリスト
	static std::unordered_map<int, std::function<bool(ColliderComponent& Collider1, ColliderComponent& Collider2)>> m_checkCollisionFunction;
	//押し出しリスト
	static std::unordered_map<int, std::function<DirectX::SimpleMath::Vector3(ColliderComponent& Collider1, ColliderComponent& Collider2)>> m_extrusionFunction;



};



