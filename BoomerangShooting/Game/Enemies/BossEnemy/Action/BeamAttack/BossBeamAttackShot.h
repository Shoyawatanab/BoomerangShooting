/*
	@file	BossBeamAttackShot.h
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


class BossBeamAttackShot : public IAction
{
public:

	//ターゲットのオフセット
	static constexpr DirectX::SimpleMath::Vector3 TARGET_OFFSET{ 0.0f,1.0f,0.0f };

	//
	static constexpr float SHOT_SPEED = 20.0f;

public:
	//コンストラクタ
	BossBeamAttackShot(Actor* bossEnemy
		, BossEnemyBeam* beam
		, BossBeamAttackActionController* beamAttack
		, Actor* player);

	//デストラクタ
	~BossBeamAttackShot() override;
	// 更新処理
	ActionState Update(const float& deltaTime);
	//状態に入った時
	void Enter();
	//状態を抜けた時
	void Exit();
private:
	//所有者
	Actor* m_bossEnemy;
	//ビーム
	BossEnemyBeam* m_beam;
	//ビーム攻撃
	BossBeamAttackActionController* m_beamAttack;
	//プレイヤ
	Actor* m_player;
	//移動方向
	DirectX::SimpleMath::Vector3 m_moveDirection;

};
