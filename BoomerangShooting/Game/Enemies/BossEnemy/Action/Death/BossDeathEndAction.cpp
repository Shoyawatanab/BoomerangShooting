#include "pch.h"
#include "BossDeathEndAction.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Enemies/EnemyManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
BossDeathEndAction::BossDeathEndAction(BossEnemy* bossEnemy)
	:
	m_bossEnemy{bossEnemy}
{



}

/// <summary>
/// デストラクタ
/// </summary>
BossDeathEndAction::~BossDeathEndAction()
{
	// do nothing.
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossDeathEndAction::ActionState BossDeathEndAction::Update(const float& deltaTime)
{
	return ActionState::RUNNING;

}



/// <summary>
/// 状態に入った時
/// </summary>
void BossDeathEndAction::Enter()
{
	
	//マネージャーに死亡の通知
	m_bossEnemy->GetEnemyManger()->DeathEnemy(m_bossEnemy);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BossDeathEndAction::Exit()
{
}
