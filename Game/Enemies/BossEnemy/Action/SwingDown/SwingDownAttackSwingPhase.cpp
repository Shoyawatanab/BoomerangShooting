/*
	クラス名     : SwingDownAttackSwingPhase
	説明         : ボス敵の振り下ろし攻撃の振り下し状態
	補足・注意点 :
*/
#include "pch.h"
#include "SwingDownAttackSwingPhase.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Player/Player.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
SwingDownAttackSwingPhase::SwingDownAttackSwingPhase(SwingDownAttackActionController* controller
	, Actor* owner
	)
	:
	m_commonResources{}
	, m_owner{ owner }
	, m_controller{ controller }
	,m_time{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
SwingDownAttackSwingPhase::~SwingDownAttackSwingPhase()
{
	// do nothing.
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
SwingDownAttackSwingPhase::ActionState SwingDownAttackSwingPhase::Update(const float& elapsedTime)
{

	if (m_time >= SWING_TIME)
	{
		return ActionState::END;
	}

	m_time += elapsedTime;

	return ActionState::RUNNING	;

}





void SwingDownAttackSwingPhase::Enter()
{

	m_time = 0.0f;

}

void SwingDownAttackSwingPhase::Exit()
{

}
