/*
	@file	BossBeamAttackCharge.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// 前方宣言
class CommonResources;
class BossEnemyBeam;
class BossBeamAttackActionController;
class BossEnemy;




class BossBeamAttackCharge : public IAction
{
public:
	//コンストラクタ
	BossBeamAttackCharge(BossEnemy* bossEnemy
		, BossEnemyBeam* beam
		, BossBeamAttackActionController* beamAttack);


	//デストラクタ
	~BossBeamAttackCharge() override;
	// 更新処理
	ActionState Update(const float& elapsedTime) override;

	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//ボステキ
	BossEnemy* m_bossEnemy;
	//ビーム
	BossEnemyBeam* m_beam;
	//時間
	float m_time;
	//パーティクル生成時間
	float m_particleCreateTime;


};
