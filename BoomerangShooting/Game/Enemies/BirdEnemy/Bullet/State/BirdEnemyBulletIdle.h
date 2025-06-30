#pragma once
#include "GameBase/Interface/IState.h"

class BirdEnemyBulletStateMachine;
class BirdEnemyBullet;
class BirdEnemy;

class BirdEnemyBulletIdle :public IState
{
public:
	//コンストラク
	BirdEnemyBulletIdle(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet, BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyBulletIdle() override;

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
};

