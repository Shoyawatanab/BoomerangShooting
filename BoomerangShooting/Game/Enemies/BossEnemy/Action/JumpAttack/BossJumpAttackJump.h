/*
	@file	BossJumpAttackJump.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// 前方宣言
class CommonResources;
class BossJumpAttackActionController;
class Player;
class BossEnemy;


class BossJumpAttackJump : public IAction
{


public:
	//コンストラクタ
	BossJumpAttackJump(BossJumpAttackActionController* controller
		,BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossJumpAttackJump() override ;
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
	BossEnemy* m_bossEnemy;
	//プレイヤ
	Player* m_player;
	//コントローラー
	BossJumpAttackActionController* m_controller;
	//ジャンプ方向
	DirectX::SimpleMath::Vector3 m_jumpDirection;
	//
	DirectX::SimpleMath::Vector3 m_startPosition;
	//
	DirectX::SimpleMath::Vector3 m_targetPosition;

	float m_time;

};
