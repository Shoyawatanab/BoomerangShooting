/*
	@file	BossBeamAttackActionController.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Action/ActionController.h"
#include "GameBase/Actor.h"
#include "Game/Enemies/BossEnemy/Action/BeamAttack/BossBeamAttackCharge.h"
#include "Game/Enemies/BossEnemy/Action/BeamAttack/BossBeamAttackEnd.h"
#include "Game/Enemies/BossEnemy/Action/BeamAttack/BossBeamAttackPreliminaryAction.h"
#include "Game/Enemies/BossEnemy/Action/BeamAttack/BossBeamAttackShot.h"

#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

// 前方宣言
class CommonResources;
class BossEnemyBeam;
class BossEnemy;

class BossBeamAttackActionController : public ActionController , public IObserver<SceneMessageType>
{
public:
	//コンストラクタ
	BossBeamAttackActionController(BossEnemy* bossEnemy
		, BossEnemyBeam* beam
		, Actor* player);
	//デストラクタ
	~BossBeamAttackActionController() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:
	// 共通リソース
	CommonResources* m_commonResources;
	//予備動作
	std::unique_ptr<BossBeamAttackPreliminaryAction> m_preliminaryAction;
	//チャージ
	std::unique_ptr<BossBeamAttackCharge> m_charge;
	//ショット
	std::unique_ptr<BossBeamAttackShot> m_shot;
	//攻撃終了
	std::unique_ptr<BossBeamAttackEnd> m_attackEnd;

};
