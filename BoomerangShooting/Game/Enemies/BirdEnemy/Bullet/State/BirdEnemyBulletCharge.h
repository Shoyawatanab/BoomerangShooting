#pragma once
#pragma once
#include "GameBase/Interface/IState.h"


class BirdEnemy;
class BirdEnemyBulletStateMachine;
class BirdEnemyBullet;


class BirdEnemyBulletCharge :public IState
{
public:
	//チャージ時間
	static constexpr float CHARGE_TIME = { 3.0f };

public:
	//コンストラク
	BirdEnemyBulletCharge(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet,BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyBulletCharge() override;

	// 更新する
	void Update(const float& deltaTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:
	//弾
	BirdEnemyBullet* m_bullet;
	//ステートマシン
	BirdEnemyBulletStateMachine* m_stateMahine;
	//鳥敵
	BirdEnemy* m_birdEnemy;
	//時間
	float m_time;



};

