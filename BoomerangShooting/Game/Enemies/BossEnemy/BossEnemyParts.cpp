#include "pch.h"
#include "BossEnemyParts.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="partsName">パーツ名</param>
/// <param name="modelName">モデル名</param>
/// <param name="hp">パーツHP</param>
/// <param name="boss">大本のクラス</param>
BossEnemyParts::BossEnemyParts(Scene* scene, std::string partsName,std::string modelName
	,int hp, DirectX::SimpleMath::Vector3 boxColliderExtens, float sphereRadius
	, BossEnemy* boss)
	:
	ModelPartsBase(scene,partsName,modelName)
	,m_hp{}
	,m_bossEnemy{boss}
{

	auto obb = AddComponent<OBB>(this, ColliderComponent::ColliderTag::OBB, CollisionType::TRIGGER
		, boxColliderExtens
		, DirectX::SimpleMath::Quaternion::Identity
		, sphereRadius);

	obb->SetNotHitObjectTag({
		Actor::ObjectTag::BOSS_ENEMY
		});

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyParts::~BossEnemyParts()
{
}

/// <summary>
/// 当たった時の関数
/// </summary>
/// <param name="collider">相手のコライダー</param>
void BossEnemyParts::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case ObjectTag::BOOMERANG:
		{
			//パーツのHp減少
			HpDecrease(Params::BOOMERANG_DAMAGE);

			//構造体の作成
			EnemyDamageDatas datas;
			//データのセット
			datas.Damage = Params::BOOMERANG_DAMAGE;
			datas.Position = GetTransform()->GetWorldPosition();


			SceneMessenger::GetInstance()->Notify(SceneMessageType::ENEMY_DAMAGE, &datas);

			//ボス敵にダメージの加算
			m_bossEnemy->AddDamage(Params::BOOMERANG_DAMAGE);
		}
			break;
		default:
			break;
	}

	OnCollisionEnterActor(collider);

}

/// <summary>
/// HP減少
/// </summary>
/// <param name="damage">ダメージ</param>
void BossEnemyParts::HpDecrease(int damage)
{

	m_hp -= damage;

	m_hp = std::max(m_hp, 0);

}
