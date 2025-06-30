#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"


class BirdEnemyBullet;
class BirdEnemy;

//状態
enum class BirdEnemyBulletState
{
	IDEL                                  //通常
	,CHAGE                                //チャージ
	,SHOT						          //ショット
};


class BirdEnemyBulletStateMachine : public StateMachine<IState, BirdEnemyBulletState> 
{
public:
	//コンストラク
	BirdEnemyBulletStateMachine(BirdEnemyBullet* bullet, BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyBulletStateMachine() override ;



};


