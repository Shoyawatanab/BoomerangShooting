/*
	@file	SwingDownAttackActionController.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Action/ActionController.h"
#include "GameBase/Actor.h"
#include "Game/Enemies/BossEnemy/Action/SwingDown/SwingDownAttackRaisePhase.h"
#include "Game/Enemies/BossEnemy/Action/SwingDown/SwingDownAttackSwingPhase.h"

// 前方宣言
class CommonResources;


class SwingDownAttackActionController : public ActionController 
{

public:

	static  constexpr float JUMPPOWER = 0.3f;

	static  constexpr float MOVESPEED = 9.0f;



public:
	//コンストラクタ
	SwingDownAttackActionController(Actor* owner);

	//デストラクタ
	~SwingDownAttackActionController()override;


private:
	// 共通リソース
	CommonResources* m_commonResources;

	//振り上げ
	std::unique_ptr<SwingDownAttackRaisePhase> m_raisePhase;
	//振り下ろし
	std::unique_ptr<SwingDownAttackSwingPhase> m_swingPhase;

};
