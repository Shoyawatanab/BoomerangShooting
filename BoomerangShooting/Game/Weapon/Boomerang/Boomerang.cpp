#include "pch.h"
#include "Boomerang.h"
#include "GameBase/Component/Components.h"
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
{

	//当たり判定の作成
	auto aabbCollider = AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, Params::BOOMERANG_BOX_COLLIDER_SIZE
		, Params::BOOMERANG_SPHERE_COLLIDER_SIZE);
	//当たり判定を無効に
	aabbCollider->SetActive(false);

	aabbCollider->SetNotHitObjectTag({
		Actor::ObjectTag::PLAYER
		,Actor::ObjectTag::PLAYER_PARTS
		});

	auto shadow = AddComponent<RoundShadowComponent>(this, Params::PLAYER_SHADOW_RADIUS);


	//初期情報の適用
	GetTransform()->SetScale(Params::BOOMERANG_SCALE);
	GetTransform()->Translate(Params::Params::BOOMERANG_POSITION);
	GetTransform()->SetRotate(Params::Params::BOOMERANG_ROTATION);



	auto model = AddComponent<ModelComponent>(this, "Boomerang");

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
}

/// <summary>
/// 当たった時の関数
/// </summary>
/// <param name="collider"></param>
void Boomerang::OnCollisionEnter(ColliderComponent* collider)
{

}

/// <summary>
/// ステートの変更
/// </summary>
/// <param name="state">次のステート</param>
void Boomerang::ActorChangeState(WeaponState nextState)
{

	switch (nextState)
	{
		case WeaponBase::WeaponState::BOOMERANG_IDLE:
			m_stateMachine->ChangeState(BoomerangState::IDEL);
			break;
		case WeaponBase::WeaponState::BOOMERANG_GET_READY:
			m_stateMachine->ChangeState(BoomerangState::GET_READY);
			break;
		case WeaponBase::WeaponState::BOOMERANG_THROW:
			m_stateMachine->ChangeState(BoomerangState::THROW);
			break;
		default:
			break;
	}

}
