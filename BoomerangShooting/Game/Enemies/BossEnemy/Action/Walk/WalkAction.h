/*
	@file	WalkAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// 前方宣言
class BossEnemy;
class CommonResources;

class WalkAction : public IAction
{

public:

	static  constexpr float ROTATESPEED = 1.0f;

	//歩く時間
	static constexpr float WALK_TIME = 4.0f;


public:
	//コンストラクタ
	WalkAction(BossEnemy* own
		, Actor* target);
	//デストラクタ
	~WalkAction() override ;
	//更新処理
	ActionState Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
	//状態を抜けた時
	void Exit() override;



private:
	// 共通リソース
	CommonResources* m_commonResources;
	//ターゲット
	Actor* m_target;
	//所有者
	BossEnemy* m_own;
	//時間
	float m_time;
};
