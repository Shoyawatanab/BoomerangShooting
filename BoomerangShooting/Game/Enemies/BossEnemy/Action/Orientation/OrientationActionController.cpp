/*
	@file	OrientationActionController.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "OrientationActionController.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
OrientationActionController::OrientationActionController(BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{}
{

	m_commonResources = CommonResources::GetInstance();

	//各状態を作成
	m_orientation = std::make_unique<OrientationAction>(bossenemy, player);


	//m_currentState->Enter();


	//動作順に追加
	AddAction({
		m_orientation.get()
		});


}

/// <summary>
/// デストラクタ
/// </summary>
OrientationActionController::~OrientationActionController()
{
	// do nothing.
}






