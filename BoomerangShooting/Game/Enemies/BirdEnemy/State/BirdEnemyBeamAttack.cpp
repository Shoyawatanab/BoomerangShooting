#include "pch.h"
#include "BirdEnemyBeamAttack.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStateMachine.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="stateMachine">ステートマシン</param>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyBeamAttack::BirdEnemyBeamAttack(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy)
	:
	m_stateMahine{ stateMachine }
	, m_birdEnemy{ birdEnemy }
{
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBeamAttack::~BirdEnemyBeamAttack()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BirdEnemyBeamAttack::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	//弾が発射されたらステートを切り替える



}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyBeamAttack::Enter()
{

	//非アクティブの弾の取得
	auto bullet = m_birdEnemy->GetInactiveBullet();
	//弾があれば
	if (bullet)
	{
		//状態の変更
		bullet->GetStateMachine()->ChangeState(BirdEnemyBulletState::CHAGE);
	}

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyBeamAttack::Exit()
{
}
