#pragma once
#include "GameBase/Interface/IState.h"

class BirdEnemyStateMachine;
class BirdEnemy;


class BirdEnemyIdle :public IState
{
public:
	//コンストラク
	BirdEnemyIdle(BirdEnemyStateMachine* stateMachine,BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyIdle() override;

	// 更新する
	void Update(const float& deltaTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:
	//鳥敵
	BirdEnemy* m_birdEnemy;
	//ステートマシン
	BirdEnemyStateMachine* m_stateMahine;

	//時間
	float m_time;
	//インターバル
	float m_attackInterval;

};

