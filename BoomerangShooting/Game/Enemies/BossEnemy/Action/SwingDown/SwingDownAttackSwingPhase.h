/*
	@file	SwingDownAttackSwingPhase.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// 前方宣言
class CommonResources;
class SwingDownAttackActionController;




class SwingDownAttackSwingPhase : public IAction
{
public:
	//振り下ろし時間
	static constexpr float SWING_TIME = 3.0f;


public:
	//コンストラクタ
	SwingDownAttackSwingPhase(SwingDownAttackActionController* controller
		, Actor* owner
		);
	//デストラクタ
	~SwingDownAttackSwingPhase() override ;
	//更新処理
	ActionState Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
	//状態を抜けた時
	void Exit() override;

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//所有者
	Actor* m_owner;
	//コントローラー
	SwingDownAttackActionController* m_controller;


	float m_time;
	

};
