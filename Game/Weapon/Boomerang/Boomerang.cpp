/*
	クラス名     : Boomerang
	説明         : ブーメラン
	補足・注意点 :
*/
#include "pch.h"
#include "Boomerang.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="player">プレイヤ</param>
Boomerang::Boomerang(Scene* scene,Player* player)
	:
	WeaponBase(scene)
	,m_lastPosition{}
{

	//当たり判定の作成
	auto aabbCollider = AddComponent<AABB>(this, CollisionType::COLLISION
		, Params::BOOMERANG_BOX_COLLIDER_SIZE
		, Params::BOOMERANG_SPHERE_COLLIDER_SIZE);

	//当たり判定を無効に
	aabbCollider->SetActive(false);

	aabbCollider->SetNotHitObjectTag({
		Actor::ObjectTag::PLAYER
		,Actor::ObjectTag::PLAYER_PARTS
		});

	auto shadow = AddComponent<RoundShadowComponent>(this, Params::PLAYER_SHADOW_RADIUS);

	auto rigidbody = AddComponent<RigidbodyComponent>(this);
	rigidbody->SetActive(false);

	auto pcikable = AddComponent<PickableComponent>(this,PickUpManager::PickUpType::PLAYER_PICKUP_WEAPON);
	pcikable->SetOnPickUpFunction(std::bind(&Boomerang::PickUp,this));

	//爆発音の作成
	m_strikeSE = AddComponent<SoundComponent>(this, "BoomerangHit", SoundComponent::SoundType::SE);


	//初期情報の適用
	GetTransform()->SetScale(Params::BOOMERANG_SCALE);
	GetTransform()->Translate(Params::Params::BOOMERANG_POSITION);
	GetTransform()->SetRotate(Params::Params::BOOMERANG_ROTATION);



	AddComponent<ModelComponent>(this, "Boomerang");

	m_stateMachine = std::make_unique<BoomerangStateMachine>(this, player);

	shadow->SetActive(false);

}

/// <summary>
/// デストラクタ
/// </summary>
Boomerang::~Boomerang()
{

}

/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime"></param>
void Boomerang::UpdateActor(const float& deltaTime)
{
	m_stateMachine->Update(deltaTime);

	//座標の保存
	m_lastPosition = GetTransform()->GetPosition();

}


/// <summary>
/// 当たった時の関数
/// </summary>
/// <param name="collider"></param>
void Boomerang::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:

			if (m_stateMachine->GetCurrentState() == BoomerangState::THROW)
			{
				m_stateMachine->ChangeState(BoomerangState::BOUNCE);
			}
			else if (m_stateMachine->GetCurrentState() == BoomerangState::BOUNCE)
			{
				m_stateMachine->ChangeState(BoomerangState::DORP);
			}
			break;
		case Actor::ObjectTag::BOSS_ENEMY_PARTS:
			m_strikeSE->Play();
			break;
		default:
			break;
	}

}

/// <summary>
/// ステートの変更
/// </summary>
/// <param name="state">次のステート</param>
void Boomerang::ActorChangeState(BoomerangState nextState)
{

	switch (nextState)
	{
		case BoomerangState::IDEL:
			m_stateMachine->ChangeState(BoomerangState::IDEL);
			break;
		case BoomerangState::GET_READY:
			m_stateMachine->ChangeState(BoomerangState::GET_READY);
			break;
		case BoomerangState::THROW:
			m_stateMachine->ChangeState(BoomerangState::THROW);
			break;
		default:
			break;
	}

}

/// <summary>
/// 回収
/// </summary>
void Boomerang::PickUp()
{
	m_stateMachine->ChangeState(BoomerangState::IDEL);
}
