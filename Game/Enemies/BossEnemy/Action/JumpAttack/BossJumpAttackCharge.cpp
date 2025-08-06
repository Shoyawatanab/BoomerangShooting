/*
	クラス名     : BossJumpAttackCharge
	説明         : ボス敵のジャンプ攻撃のチャージ状態
	補足・注意点 :
*/
#include "pch.h"
#include "BossJumpAttackCharge.h"
#include "GameBase/Common/Commons.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/Action/JumpAttack/BossJumpAttackActionController.h"
#include "Game/Messenger/Messengers.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossJumpAttackCharge::BossJumpAttackCharge(BossJumpAttackActionController* controller
	,Actor* bossenemy
	, Actor* player)
	:
	m_commonResources{}
	,m_bossEnemy{bossenemy}
	,m_player{player}
	,m_controller{ controller }
	,m_time{}
{
	m_commonResources = CommonResources::GetInstance();

}

/// <summary>
/// デストラクタ
/// </summary>
BossJumpAttackCharge::~BossJumpAttackCharge()
{
	// do nothing.
}



BossJumpAttackCharge::ActionState BossJumpAttackCharge::Update(const float& elapsedTime)
{


	//時間はアニメーションと合わせる
	if (m_time >= CHARGE_TIME)
	{
		return ActionState::END;
	
	}

	
	m_time += elapsedTime;

	return ActionState::RUNNING;

}


void BossJumpAttackCharge::Enter()
{

	m_time = 0;

	auto  startPosition = m_bossEnemy->GetTransform()->GetPosition();

	auto targetPosition = m_player->GetTransform()->GetPosition();

	auto jumpDirection = targetPosition - startPosition;

	m_controller->SetJumpDirection(jumpDirection);

	CreateChargeEffectDatas datas;
	datas.Position = m_bossEnemy->GetTransform()->GetWorldPosition();
	datas.Scale = m_bossEnemy->GetTransform()->GetWorldScale();

	datas.Position.y = 0.1f;

	//エフェクト作成の通知
	Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::CREATE_CHARGE_EFFECT, &datas);
	//ジャンプアニメーションの通知
	Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::BOSS_JUMP_ANIMATION_START);

}

void BossJumpAttackCharge::Exit()
{
}
