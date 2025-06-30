/*
	@file	BossBeamAttackPreliminaryAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackPreliminaryAction.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="bossEnemy">所有者</param>
/// <param name="beam">ビーム</param>
/// <param name="beamAttack">ビーム攻撃</param>
BossBeamAttackPreliminaryAction::BossBeamAttackPreliminaryAction(Actor* bossEnemy
	, BossEnemyBeam* beam
	, BossBeamAttackActionController* beamAttack)
	:
	m_commonResources{}
	,m_time{}
	, m_bossEnemy{ bossEnemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackPreliminaryAction::~BossBeamAttackPreliminaryAction()
{
	// do nothing.
}



/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossBeamAttackPreliminaryAction::ActionState BossBeamAttackPreliminaryAction::Update(const float& elapsedTime)
{

	if (m_time >= Params::BOSSENEMY_BEAM_BALL_PRELIMINARY_ACTION_TIME)
	{
		return ActionState::END;
	}



	m_time += elapsedTime;

	return ActionState::RUNNING;

}

/// <summary>
/// 状態に入った時
/// </summary>
void BossBeamAttackPreliminaryAction::Enter()
{

	m_time = 0.0f;


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BossBeamAttackPreliminaryAction::Exit()
{



}
