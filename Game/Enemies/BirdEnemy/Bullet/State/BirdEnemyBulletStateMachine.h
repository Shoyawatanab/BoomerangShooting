/*
	クラス名     : BirdEnemyBulletStateMachine
	説明         : 鳥敵の弾のステートマシーン
	補足・注意点 :
*/
#pragma once
#include "GameBase/StateMachine/StateMachine.h"


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


