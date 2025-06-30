/*
	@file	BossBeamAttackPreliminaryAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// 前方宣言
class CommonResources;
class BossEnemyBeam;
class BossBeamAttackActionController;





class BossBeamAttackPreliminaryAction : public IAction
{
public:
	//コンストラクタ
	BossBeamAttackPreliminaryAction(Actor* bossEnemy
		, BossEnemyBeam* beam
		, BossBeamAttackActionController* beamAttack);

	
	//デストラクタ
	~BossBeamAttackPreliminaryAction() override;
	// 更新処理
	ActionState Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override ;
private:
	// 共通リソース
	CommonResources* m_commonResources;

	//経過時間
	float m_time;
	//所有者
	Actor* m_bossEnemy;
	//ビーム
	BossEnemyBeam* m_beam;
	//ビーム攻撃
	BossBeamAttackActionController* m_beamAttack;


};
