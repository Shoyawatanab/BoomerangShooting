/*
	@file	BossBeamAttackEnd.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// 前方宣言
class CommonResources;
class BossEnemyBeam;
class BossBeamAttackActionController;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeamAttackEnd : public IAction
{
public:

	//終了時の時間　　アニメーション終了時と合わせる
	static constexpr float END_TIME = { 2.0f };

public:
	//コンストラクタ
	BossBeamAttackEnd(Actor* bossEnemy
		, BossEnemyBeam* beam
		, BossBeamAttackActionController* beamAttack);


	//デストラクタ
	~BossBeamAttackEnd() override ;
	// 更新する
	ActionState Update(const float& elapsedTime);
	//状態に入った時
	void Enter();
	//状態を抜けた時
	void Exit();
private:
	// 共通リソース
	CommonResources* m_commonResources;
	//所有者
	Actor* m_bossEnemy;
	//ビーム
	BossEnemyBeam* m_beam;
	//ビーム攻撃
	BossBeamAttackActionController* m_beamAttack;
	//経過時間
	float m_time;
	//状態に張った時のスケール
	DirectX::SimpleMath::Vector3 m_initalScale;

};
