#pragma once
#include "GameBase/StateMachine/StateMachine.h"

class BirdEnemy;

enum class BirdEnemyState
{
	IDEL                                  //通常
	,MOVE                                 //動き
	,BULLET_ATTACK						  //ビーム攻撃
};


class BirdEnemyStateMachine : public StateMachine<IState, BirdEnemyState> 
{
public:
	//コンストラク
	BirdEnemyStateMachine(BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyStateMachine() override ;



};


