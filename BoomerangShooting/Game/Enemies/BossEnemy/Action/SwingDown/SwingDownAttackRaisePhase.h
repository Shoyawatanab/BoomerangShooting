/*
	@file	SwingDownAttackRaisePhase.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// 前方宣言
class CommonResources;
class SwingDownAttackActionController;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class SwingDownAttackRaisePhase : public IAction
{
public:
	//振り上げ時間
	static constexpr float RAISE_TIME = 2.0f;

public:
	//コンストラクタ
	SwingDownAttackRaisePhase(SwingDownAttackActionController* controller
		, Actor* owner
		);
	//デストラクタ
	~SwingDownAttackRaisePhase() override ;
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
	//時間
	float m_time;
	//コントローラー
	SwingDownAttackActionController* m_controller;


};
