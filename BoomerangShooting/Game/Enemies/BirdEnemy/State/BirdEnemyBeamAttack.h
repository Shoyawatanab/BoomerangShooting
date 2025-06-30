#pragma once
#include "GameBase/Interface/IState.h"

class BirdEnemyStateMachine;
class BirdEnemy;


class BirdEnemyBeamAttack :public IState
{
public:
	//コンストラク
	BirdEnemyBeamAttack(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyBeamAttack() override;

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

};


