#include "pch.h"
#include "BossDeathAction.h"
#include "Game/Messenger/Scene/SceneMessages.h"


/// <summary>
/// コンストラクタ
/// </summary>
BossDeathAction::BossDeathAction()
	:
	m_time{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
BossDeathAction::~BossDeathAction()
{
	// do nothing.
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossDeathAction:: ActionState BossDeathAction::Update(const float& deltaTime)
{
	//アニメーションが追わったら
	if (m_time >= DEATH_TIME)
	{
		return ActionState::END;

	}


	m_time += deltaTime;

	return ActionState::RUNNING;

}



/// <summary>
/// 状態に入った時
/// </summary>
void BossDeathAction::Enter()
{
	SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_DEFEATED);

	m_time = 0;
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BossDeathAction::Exit()
{
}
