/*
	@file	SwingDownAttackRaisePhase.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "SwingDownAttackRaisePhase.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>


#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/Action/SwingDown/SwingDownAttackActionController.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="controller">コントローラー</param>
/// <param name="owner">所有者</param>
SwingDownAttackRaisePhase::SwingDownAttackRaisePhase(SwingDownAttackActionController* controller
	, Actor* owner
	)
	:
	m_commonResources{}
	, m_owner{ owner }
	, m_controller{controller}
	,m_time{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
SwingDownAttackRaisePhase::~SwingDownAttackRaisePhase()
{
	// do nothing.
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
SwingDownAttackRaisePhase::ActionState SwingDownAttackRaisePhase::Update(const float& elapsedTime)
{
	//時間はアニメーションと合わせる
	if (m_time >= RAISE_TIME)
	{
		return ActionState::END;
	}

	
	m_time += elapsedTime;

	return ActionState::RUNNING;

}



/// <summary>
/// 状態に入った時
/// </summary>
void SwingDownAttackRaisePhase::Enter()
{

	m_time = 0;



}

/// <summary>
/// 状態を抜けた時
/// </summary>
void SwingDownAttackRaisePhase::Exit()
{
}
