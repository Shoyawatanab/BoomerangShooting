/*
	@file	BossJumpAttackActionController.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossJumpAttackActionController.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossJumpAttackActionController::BossJumpAttackActionController(BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{}
{

	m_commonResources = CommonResources::GetInstance();

	//各状態を作成
	m_charge = std::make_unique<BossJumpAttackCharge>(this,bossenemy,player);
	m_jump = std::make_unique<BossJumpAttackJump>( this, bossenemy, player);
	m_orientation = std::make_unique<OrientationAction>(bossenemy, player);


	//m_currentState->Enter();


	//動作順に追加
	AddAction({
		m_orientation.get(),
		m_charge.get(),
		m_jump.get()
		});


}

/// <summary>
/// デストラクタ
/// </summary>
BossJumpAttackActionController::~BossJumpAttackActionController()
{
	// do nothing.
}






