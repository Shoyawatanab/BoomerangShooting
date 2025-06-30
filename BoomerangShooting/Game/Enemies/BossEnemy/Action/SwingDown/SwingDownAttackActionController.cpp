/*
	@file	SwingDownAttackActionController.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "SwingDownAttackActionController.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">経過時間</param>
/// <param name="owner">所有者</param>
SwingDownAttackActionController::SwingDownAttackActionController(Actor* owner)
	:
	m_commonResources{}
{

	//各状態の作成
	m_raisePhase = std::make_unique<SwingDownAttackRaisePhase>(this, owner);

	m_swingPhase = std::make_unique<SwingDownAttackSwingPhase>(this, owner);


	//m_currentState->Enter();


	//動作順に追加
	AddAction({
		m_raisePhase.get()
		,m_swingPhase.get()
		});


}

/// <summary>
/// デストラクタ
/// </summary>
SwingDownAttackActionController::~SwingDownAttackActionController()
{
	// do nothing.
}







