/*
	@file	BossJumpAttackCharge.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// 前方宣言
class CommonResources;
class Beam;
class BossJumpAttackActionController;




class BossJumpAttackCharge : public IAction
{

public:

	//エフェクトの大きさ
	static constexpr DirectX::SimpleMath::Vector3 EFFECTE_SCALE{ 5.0f,5.0f,5.0f };
	//チャージ時間
	static constexpr float CHARGE_TIME = 1.5f;

public:
	//コンストラクタ
	BossJumpAttackCharge(BossJumpAttackActionController* controller
		,Actor* bossEnemy
		,Actor* player);
	//デストラクタ
	~BossJumpAttackCharge() override ;
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
	Actor* m_bossEnemy;
	//プレイヤ
	Actor* m_player;
	//時間
	float m_time;
	//コントローラー
	BossJumpAttackActionController* m_controller;


};
