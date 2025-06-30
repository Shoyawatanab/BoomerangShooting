#include "pch.h"
#include "BirdEnemyBulletStateMachine.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStates.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStates.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyBulletStateMachine::BirdEnemyBulletStateMachine(BirdEnemyBullet* bullet, BirdEnemy* birdEnemy)
{

	//IDEL状態の追加
	AddState(BirdEnemyBulletState::IDEL, std::make_unique<BirdEnemyBulletIdle>(this, bullet,birdEnemy));
	//Chage状態の追加
	AddState(BirdEnemyBulletState::CHAGE, std::make_unique<BirdEnemyBulletCharge>(this, bullet,birdEnemy));
	//Shot状態の追加
	AddState(BirdEnemyBulletState::SHOT, std::make_unique<BirdEnemyBulletShot>(this, bullet,birdEnemy));

	//初期ステートの設定
	SetStartState(BirdEnemyBulletState::IDEL);





}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBulletStateMachine::~BirdEnemyBulletStateMachine()
{
}


