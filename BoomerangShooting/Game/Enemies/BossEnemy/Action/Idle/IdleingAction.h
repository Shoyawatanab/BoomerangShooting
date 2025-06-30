/*
	@file	IdleingAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"



class IdleingAction : public IAction
{
public:
	//コンストラクタ
	IdleingAction();
	//デストラクタ
	~IdleingAction() override ;
	//更新処理
	ActionState Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
	//状態を抜けた時
	void Exit() override;

};
