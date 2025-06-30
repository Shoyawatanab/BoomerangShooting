/*
	@file	BossJumpAttackCharge.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossJumpAttackCharge.h"
#include "GameBase/Common/Commons.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "GameBase/Component/Components.h"


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

	CreateChargeEffectDatas datas;
	datas.Position = m_bossEnemy->GetTransform()->GetWorldPosition();
	datas.Scale = m_bossEnemy->GetTransform()->GetWorldScale();

	datas.Position.y = 0.1f;

	SceneMessenger::GetInstance()->Notify(SceneMessageType::CREATE_CHARGE_EFFECT, &datas);

}

void BossJumpAttackCharge::Exit()
{
}
