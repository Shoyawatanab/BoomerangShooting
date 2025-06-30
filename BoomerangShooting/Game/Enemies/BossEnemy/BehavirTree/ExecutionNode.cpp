#include "pch.h"
#include "ExecutionNode.h"
#include "GameBase/Common/Commons.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"

#include "Game/Messenger/Scene/SceneMessages.h"



static const float ROTATESPEED = 1.0f;
static const float PATROLSPEED = 2.0f;;

/// <summary>
/// 
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
ExecutionNode::ExecutionNode(Player* player, BossEnemy* enemy)
	:
	m_commonResources{},
	m_palyer{ player },
	m_enemy{ enemy }
{

}

/// <summary>
/// デストラクタ
/// </summary>
ExecutionNode::~ExecutionNode()
{

}




/// <summary>
/// ビーム攻撃
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::BossEnemyBeamAction()
{

	SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_BEAM_ATTACK_STATE);


	return IBehaviorNode::State::SUCCESS;

}



/// <summary>
/// ジャンプ攻撃
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::BossEnemyJumpAttackAction()
{

	SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_JUMP_ATTACK_STATE);

	return IBehaviorNode::State::SUCCESS;

}

/// <summary>
/// 歩き
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::BossEnemyWalking()
{
	SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_WAKING_STATE);

	return IBehaviorNode::State::SUCCESS;

}

/// <summary>
/// 振り下ろし攻撃
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::BossEnemySwingDown()
{

	SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_SWING_DOWN_STATE);


	return IBehaviorNode::State::SUCCESS;
}


