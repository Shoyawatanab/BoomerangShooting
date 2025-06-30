/*
	@file	BossBeam.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Actor.h"

// 前方宣言
class CommonResources;
class BossBeamEnergyBall;
class BossBeamRays;
class BossBeamStateMachine;
class Player;
class BossEnemy;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeam : public Actor
{
public:

	//チャージエフェクトの大きさ
	static constexpr DirectX::SimpleMath::Vector3 EFFECT_SCALE{ 0.1f,0.1f,0.1f };

public:

	//ビームの取得
	BossBeamEnergyBall* GetBossBeamEnergyBall() { return m_energyBall.get(); }
	//光線の取得
	BossBeamRays* GetBossBeamRays() { return m_rays.get(); }



public:
	//コンストラク
	BossBeam(Scene* scene);
	//デストラクタ
	~BossBeam() override;


	//初期化
	void Initialize() override;
	//更新処理
	void  UpdateActor(const float& deltatime) override;




private:
	//エネルギー弾
	std::unique_ptr<BossBeamEnergyBall> m_energyBall;
	//予備動作時間
	float m_preliminaryActitonTime;
	//光線
	std::unique_ptr<BossBeamRays> m_rays;
	//プレイヤ
	Player* m_player;

};
