#include "pch.h"
#include "CollisionManager.h"
#include "GameBase/Component/Collider/ColliderComponent.h"
#include "GameBase/Component/Collider/DetectionCollision2.h"
#include <algorithm> 

/// <summary>
/// コンポーネント
/// </summary>
CollisionManager::CollisionManager()
	:
	m_colliderList{}
{
}


/// <summary>
/// デストラクタ
/// </summary>
CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update(const float& deltaTime)
{

	if (m_colliderList.empty()) { return; }


	for (int i = 0; i < m_colliderList.size() - 1; i++)
	{
		//有効出ないなら
		if (!m_colliderList[i]->GetActive())
		{
			continue;
		}

		for (int j = i + 1 ; j < m_colliderList.size(); j++)
		{
			//有効できないなら
			if (!m_colliderList[j]->GetActive()){continue;}
			//同じオブジェクトなら
			if (m_colliderList[i]->GetActor() == m_colliderList[j]->GetActor())	{continue;}
			//固定オブジェクト同士なら
			if (m_colliderList[i]->GetCollisionType() == CollisionType::FIXED && m_colliderList[j]->GetCollisionType() == CollisionType::FIXED) { continue; }

			//タグの取得
			auto tag = m_colliderList[i]->GetActor()->GetObjectTag();

			//当たり判定を行わないタグの取得
			auto notHitObjectTag = m_colliderList[j]->GetNotHitObjectTag();

			//当たり判定を行わないタグの判定
			if (std::find(notHitObjectTag.begin(), notHitObjectTag.end(), tag) != notHitObjectTag.end())
			{
				//行わない
				continue;
			}



			//移動オブジェクト同士
			if (m_colliderList[i]->GetCollisionType() == CollisionType::COLLISION && m_colliderList[j]->GetCollisionType() == CollisionType::COLLISION)
			{
				Collision_Collision(m_colliderList[i], m_colliderList[j]);
			}
			//固定オブジェクト同士
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::FIXED && m_colliderList[j]->GetCollisionType() == CollisionType::FIXED)
			{
				Fixed_Fixed(m_colliderList[i], m_colliderList[j]);
			}
			//すり抜けオブジェクト同士
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::TRIGGER && m_colliderList[j]->GetCollisionType() == CollisionType::TRIGGER)
			{
				Trigger_Trigger(m_colliderList[i], m_colliderList[j]);
			}
			//固定オブジェクトと移動オブジェクト
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::FIXED && m_colliderList[j]->GetCollisionType() == CollisionType::COLLISION)
			{
				Fixed_Collision(m_colliderList[i], m_colliderList[j]);
			}
			//固定オブジェクトとすり抜けオブジェクト
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::FIXED && m_colliderList[j]->GetCollisionType() == CollisionType::TRIGGER)
			{
				Fixed_Trigger(m_colliderList[i], m_colliderList[j]);
			}
			//移動オブジェクトとすり抜けオブジェクト
			else if (m_colliderList[i]->GetCollisionType() == CollisionType::COLLISION && m_colliderList[j]->GetCollisionType() == CollisionType::TRIGGER)
			{
				Collision_Trigger(m_colliderList[i], m_colliderList[j]);
			}
		}
	}


}


/// <summary>
/// コライダーの追加
/// </summary>
/// <param name="collider"></param>
void CollisionManager::AddCollider(ColliderComponent* collider)
{
	//すでに追加されているか
	auto it = std::find(m_colliderList.begin(), m_colliderList.end(), collider);
	//あれば
	if (it != m_colliderList.end())
	{
		return;
	}

	//追加
	m_colliderList.push_back(collider);

	//並び替え
	std::sort(
		m_colliderList.begin(),
		m_colliderList.end(),
		[](ColliderComponent* a, ColliderComponent* b) {
			return a->GetCollisionType() < b->GetCollisionType();  // 小さい順に並べる
		}
	);

}

/// <summary>
/// コライダーの削除
/// </summary>
/// <param name="collider"></param>
void CollisionManager::RemoveCollider(ColliderComponent* collider)
{
	//すでに追加されているか
	auto it = std::find(m_colliderList.begin(), m_colliderList.end(), collider);

	//なければ
	if (it == m_colliderList.end())
	{
		return;
	}

	m_colliderList.erase(it);

}

void CollisionManager::Collision_Collision(ColliderComponent* collider1, ColliderComponent* collider2)
{
	//当たり判定フラグ
	bool isHit = DetectionCollision2::ChecOnCollision(collider1, collider2);

	//通知を送る
	SendNotification(collider1, collider2,isHit);

}

void CollisionManager::Fixed_Fixed(ColliderComponent* collider1, ColliderComponent* collider2)
{
}

void CollisionManager::Trigger_Trigger(ColliderComponent* collider1, ColliderComponent* collider2)
{
}

/// <summary>
/// 固定オブジェクトと移動オブジェクト
/// </summary>
/// <param name="collider1">コライダー１</param>
/// <param name="collider2">コライダー２</param>
void CollisionManager::Fixed_Collision(ColliderComponent* collider1, ColliderComponent* collider2)
{
	using namespace DirectX::SimpleMath;
	//当たり判定フラグ
	bool isHit = DetectionCollision2::ChecOnCollision(collider1, collider2);

	//当たったか
	if (isHit)
	{
		//当たっていたら
		//めり込み量の計算
		Vector3 pushVector = DetectionCollision2::Extrusion(collider1, collider2);
		//押し出し　並び替えてあるから２を押し出しても大丈夫
		//collider2->GetActor()->GetTransform()->Translate(-pushVector);
		collider2->SetPushBack(-pushVector);
	}

	//通知を送る
	SendNotification(collider1, collider2, isHit);
	


}

void CollisionManager::Fixed_Trigger(ColliderComponent* collider1, ColliderComponent* collider2)
{

	//当たり判定フラグ
	bool isHit = DetectionCollision2::ChecOnCollision(collider1, collider2);
	//通知を送る
	SendNotification(collider1, collider2, isHit);

}

void CollisionManager::Collision_Trigger(ColliderComponent* collider1, ColliderComponent* collider2)
{

	//当たり判定フラグ
	bool isHit = DetectionCollision2::ChecOnCollision(collider1, collider2);

	//通知を送る
	SendNotification(collider1, collider2, isHit);


}

/// <summary>
/// 通知を送る
/// </summary>
/// <param name="collider1"></param>
/// <param name="collider2"></param>
/// <param name="isHit">当たり判定の結果</param>
void CollisionManager::SendNotification(ColliderComponent* collider1, ColliderComponent* collider2,bool isHit)
{

	//当たったら
	if (isHit)
	{
		//当たったオブジェクトの取得
		std::vector<ColliderComponent*> ob = collider1->GetHitObject();

		//すでに当たっているかどうか
		if (std::find(ob.begin(), ob.end(), collider2) != ob.end())
		{
			//当たっている間呼び出される関数
			collider1->GetActor()->OnCollisionStay(collider2);
			collider2->GetActor()->OnCollisionStay(collider1);
		}
		else
		{
			//当たった時だけ呼ぶ関数
			collider1->GetActor()->OnCollisionEnter(collider2);
			collider2->GetActor()->OnCollisionEnter(collider1);
			//当たったオブジェクトのポインタを登録
			collider1->SetHitObject(collider2);
			collider2->SetHitObject(collider1);

		}

	}
	//当たっていないなら
	else
	{
		//削除
		bool isDelete = collider1->DleteHitObject(collider2);
		
		//削除できたら
		if (isDelete)
		{
			//離れた時に呼ぶ関数
			collider1->GetActor()->OnCollisionExit(collider2);
			collider2->GetActor()->OnCollisionExit(collider1);

		}

	}



}
