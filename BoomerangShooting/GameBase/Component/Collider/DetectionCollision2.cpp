#include "pch.h"
#include "DetectionCollision2.h"



//関数の登録
std::unordered_map<int, std::function<bool(ColliderComponent& object1, ColliderComponent& object2)>> DetectionCollision2::m_checkCollisionFunction = {
	{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::AABB,    DetectionCollision2::AABB_AABB_CheckCollision}
	,{(int)ColliderComponent::ColliderTag::OBB | (int)ColliderComponent::ColliderTag::OBB,     DetectionCollision2::OBB_OBB_CheckCollision}
	,{(int)ColliderComponent::ColliderTag::SPHERE | (int)ColliderComponent::ColliderTag::SPHERE,  DetectionCollision2::SPHERE_SPHERE_CheckCollision}
	,{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::OBB,     DetectionCollision2::AABB_OBB_CheckCollision}
	,{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::SPHERE,  DetectionCollision2::AABB_SPHERE_CheckCollision}

};

std::unordered_map<int, std::function<DirectX::SimpleMath::Vector3(ColliderComponent& Collider1, ColliderComponent& Collider2)>> DetectionCollision2::m_extrusionFunction = {
	{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::AABB,    DetectionCollision2::AABB_AABB_Extrusion}
	,{(int)ColliderComponent::ColliderTag::OBB | (int)ColliderComponent::ColliderTag::OBB,     DetectionCollision2::OBB_OBB_Extrusion}
	,{(int)ColliderComponent::ColliderTag::SPHERE | (int)ColliderComponent::ColliderTag::SPHERE,  DetectionCollision2::SPHERE_SPHERE_Extrusion}
	,{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::OBB,     DetectionCollision2::AABB_OBB_Extrusion}
	,{(int)ColliderComponent::ColliderTag::AABB | (int)ColliderComponent::ColliderTag::SPHERE,  DetectionCollision2::AABB_SPHERE_Extrusion}
};


/// <summary>
/// 当たったかどうかのチェック 
/// </summary>
/// <param name="collider1">コライダー１</param>
/// <param name="collier2">コライダー２</param>
/// <returns>true : 当たった  false : 当たってない</returns>
bool DetectionCollision2::ChecOnCollision(ColliderComponent* collider1, ColliderComponent* collider2)
{
	bool isHit = false;

	//元のデータに影響を与えないため　入れ替えをするため
	ColliderComponent* localObject1 = collider1;
	ColliderComponent* localObject2 = collider2;

	//並び替え　小さいほうをObject1にするようにする
	(int)localObject1->GetCollisionTag() > (int)localObject2->GetCollisionTag() ? std::swap(localObject1, localObject2) : void();

	int type = (int)localObject1->GetCollisionTag() | (int)localObject2->GetCollisionTag();

	//当たり判定の種類があるか
	auto it = m_checkCollisionFunction.find(type);


	if (it != m_checkCollisionFunction.end())
	{
		//あれば登録された関数を呼ぶ
		isHit = m_checkCollisionFunction[type](*localObject1, *localObject2);
	}

	//当たっていない
	return isHit;

}



const DirectX::SimpleMath::Vector3 DetectionCollision2::Extrusion(ColliderComponent* collider1, ColliderComponent* collider2)
{
	using namespace DirectX::SimpleMath;

	//元のデータに影響を与えないため　入れ替えをするため
	ColliderComponent* localObject1 = collider1;
	ColliderComponent* localObject2 = collider2;

	//並び替え　小さいほうをObject1にするようにする
	(int)localObject1->GetCollisionTag() > (int)localObject2->GetCollisionTag() ? std::swap(localObject1, localObject2) : void();

	int type = (int)localObject1->GetCollisionTag() | (int)localObject2->GetCollisionTag();

	//当たり判定の種類があるか
	auto it = m_extrusionFunction.find(type);


	if (it != m_extrusionFunction.end())
	{
		//あれば登録された関数を呼ぶ
		return m_extrusionFunction[type](*localObject1, *localObject2);
	}

	//当たっていない
	return Vector3::Zero;
	

}

//フリースタイル　　サクシード

/// <summary>
/// AABB同士の判定
/// </summary>
/// <param name="collider1">コライダー１</param>
/// <param name="collider2">コライダー２</param>
/// <returns>true : 当たった  false : 当たってない</returns>
bool DetectionCollision2::AABB_AABB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{

	using namespace DirectX;

	//AABBにキャスト
	AABB& aabb1 = static_cast<AABB&>(collider1);
	AABB& aabb2 = static_cast<AABB&>(collider2);
	//スフィアの取得
	BoundingSphere* sphere1 = aabb1.GetBoundingSphere();
	BoundingSphere* sphere2 = aabb2.GetBoundingSphere();
	//スフィアの判定
	if (!sphere1->Intersects(*sphere2))
	{
		return false;
	}

	//データの取得
	BoundingBox* Box1 = aabb1.GetBoundingBox();
	BoundingBox* Box2 = aabb2.GetBoundingBox();

	//判定
	if (Box1->Intersects(*Box2))
	{
		//当たった
		return true;
	}

	//当たってない
	return false;
}

bool DetectionCollision2::OBB_OBB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{

	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return false;
}

bool DetectionCollision2::SPHERE_SPHERE_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return false;
}

bool DetectionCollision2::AABB_OBB_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{
	using namespace DirectX;


	//AABBにキャスト
	AABB& aabb1 = static_cast<AABB&>(collider1);
	OBB& aabb2 = static_cast<OBB&>(collider2);
	//スフィアの取得
	BoundingSphere* sphere1 = aabb1.GetBoundingSphere();
	BoundingSphere* sphere2 = aabb2.GetBoundingSphere();
	//スフィアの判定
	if (!sphere1->Intersects(*sphere2))
	{
		return false;
	}

	////データの取得
	BoundingBox* Box1 = aabb1.GetBoundingBox();
	BoundingOrientedBox* Box2 = aabb2.GetBoundingOrientedBox();

	//判定
	if (Box1->Intersects(*Box2))
	{
		//当たった
		return true;
	}


	return false;
}

bool DetectionCollision2::AABB_SPHERE_CheckCollision(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return false;
}

/// <summary>
/// AABB同士の押し出しの計算
/// </summary>
/// <param name="collider1">コライダー１</param>
/// <param name="collider2">コライダー２</param>
/// <returns>押し出し量</returns>
DirectX::SimpleMath::Vector3 DetectionCollision2::AABB_AABB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//AABBにキャスト
	AABB& aabb1 = static_cast<AABB&>(collider1);
	AABB& aabb2 = static_cast<AABB&>(collider2);

	//ボックスの取得
	BoundingBox* Box1 = aabb1.GetBoundingBox();
	BoundingBox* Box2 = aabb2.GetBoundingBox();

	Vector3 Min1 = Box1->Center - Box1->Extents;
	Vector3 Max1 = Box1->Center + Box1->Extents;
	Vector3 Min2 = Box2->Center - Box2->Extents;
	Vector3 Max2 = Box2->Center + Box2->Extents;

	//各軸の差分の計算
	float dx1 = Max2.x - Min1.x;
	float dx2 = Min2.x - Max1.x;
	float dy1 = Max2.y - Min1.y;
	float dy2 = Min2.y - Max1.y;
	float dz1 = Max2.z - Min1.z;
	float dz2 = Min2.z - Max1.z;

	//各軸の絶対値の小さい方を軸のめり込みにする
	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
	float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

	// 押し戻しベクトル
	Vector3 pushBackVec = Vector3::Zero;

	// めり込みが一番小さい軸を押し戻す
	if (abs(dx) <= abs(dy) && abs(dx) <= abs(dz))
	{
		pushBackVec.x += dx;
	}
	else if (abs(dz) <= abs(dx) && abs(dz) <= abs(dy))
	{
		pushBackVec.z += dz;
	}
	else
	{
		pushBackVec.y += dy;
	}

	return pushBackVec;

}

DirectX::SimpleMath::Vector3 DetectionCollision2::OBB_OBB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return DirectX::SimpleMath::Vector3();
}

DirectX::SimpleMath::Vector3 DetectionCollision2::SPHERE_SPHERE_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return DirectX::SimpleMath::Vector3();
}

DirectX::SimpleMath::Vector3 DetectionCollision2::AABB_OBB_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return DirectX::SimpleMath::Vector3();
}

DirectX::SimpleMath::Vector3 DetectionCollision2::AABB_SPHERE_Extrusion(ColliderComponent& collider1, ColliderComponent& collider2)
{
	UNREFERENCED_PARAMETER(collider1);
	UNREFERENCED_PARAMETER(collider2);

	return DirectX::SimpleMath::Vector3();
}
