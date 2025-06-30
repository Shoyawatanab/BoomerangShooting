/*
	@file	WalkActionComtroller.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Action/ActionController.h"
#include "Game/Enemies/BossEnemy/Action/Walk/WalkAction.h"
#include "Game/Enemies/BossEnemy/Action/Orientation/OrientationAction.h"
#include "GameBase/Actor.h"

// 前方宣言
class BossEnemy;


class WalkActionComtroller : public ActionController
{

public:

	static  constexpr float ROTATESPEED = 1.0f;

public:
	//コンストラク
	WalkActionComtroller(BossEnemy* own
		, Actor* target);
	//デストラクタ
	~WalkActionComtroller() override;

private:
	//ターゲット
	Actor* m_target;
	//所有者
	BossEnemy* m_own;
	//歩き状態
	std::unique_ptr<WalkAction> m_walkingAction;
	//回転状態
	std::unique_ptr<OrientationAction> m_orientation;

};
