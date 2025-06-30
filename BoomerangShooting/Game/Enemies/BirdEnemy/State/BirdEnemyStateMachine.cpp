#include "pch.h"
#include "BirdEnemyStateMachine.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStates.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyStateMachine::BirdEnemyStateMachine(BirdEnemy* birdEnemy)
{

	//IDEL状態の追加
	AddState(BirdEnemyState::IDEL, std::make_unique<BirdEnemyIdle>(this, birdEnemy));
	//Move状態の追加
	AddState(BirdEnemyState::MOVE, std::make_unique<BirdEnemyMove>(this, birdEnemy));
	//BeamAttack状態の追加
	AddState(BirdEnemyState::BULLET_ATTACK, std::make_unique<BirdEnemyBeamAttack>(this, birdEnemy));

	//初期ステートの設定
	SetStartState(BirdEnemyState::IDEL);





}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyStateMachine::~BirdEnemyStateMachine()
{
}

