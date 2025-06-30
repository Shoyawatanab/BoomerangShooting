#pragma once
#include "GameBase/Interface/IState.h"

class BirdEnemyBulletStateMachine;
class BirdEnemyBullet;
class BirdEnemy;

class BirdEnemyBulletShot :public IState
{
public:
	//コンストラク
	BirdEnemyBulletShot(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet, BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyBulletShot() override;

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
	BirdEnemy* m_birdEnemy;
	//時間
	float m_time;
	//動く方向
	DirectX::SimpleMath::Vector3 m_moveDirection;
};

#pragma once
