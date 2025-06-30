#include "pch.h"
#include "BirdEnemyBulletShot.h"
#include <random>
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/MathUtil.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="stateMachine">ステートマシン</param>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyBulletShot::BirdEnemyBulletShot(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet, BirdEnemy* birdEnemy)
	:
	m_stateMahine{ stateMachine }
	,m_bullet{ bullet }
	,m_birdEnemy{birdEnemy}
	,m_time{}
	,m_moveDirection{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBulletShot::~BirdEnemyBulletShot()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BirdEnemyBulletShot::Update(const float& deltaTime)
{
	//補間のための時間を求める　　経過時間が減速時間になるまでは０～１の間　経過時間が減速時間を超えると１
	float t = std::min(m_time, Params::BIRDENEMY_BEAM_BALL_DECELERATION_TIME) / Params::BIRDENEMY_BEAM_BALL_DECELERATION_TIME;
	//初速と終速で補間して移動速度を求める
	float moveSpeed = MathUtil::Lerp(Params::BIRDENEMY_BEAM_BALL_INITIAL_SPEED, Params::BIRDENEMY_BEAM_BALL_FAINAL_SPEED, t);


	//auto rigidbody = m_bullet->GetComponent<RigidbodyComponent>();
	//rigidbody->SetVelocity(m_moveDirection * moveSpeed);

	m_bullet->GetTransform()->SetPosition(m_bullet->GetTransform()->GetWorldPosition() + (m_moveDirection * moveSpeed * deltaTime));

	m_time += deltaTime;
}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyBulletShot::Enter()
{


	//発射方向を計算
	m_moveDirection = m_birdEnemy->GetTarget()->GetTransform()->GetRotatePosition() - m_bullet->GetTransform()->GetRotatePosition() ;
	//m_moveDirection.Normalize();
	m_time = 0.0f;

	m_bullet->GetTransform()->SetParent(nullptr);
	//所有者の状態を変更
	m_birdEnemy->GetStateMachine()->ChangeState(BirdEnemyState::IDEL);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyBulletShot::Exit()
{
}
