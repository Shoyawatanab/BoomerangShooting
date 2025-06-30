#include "pch.h"
#include "BirdEnemyIdle.h"
#include <random>
#include "Game/Params.h"

#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/MathUtil.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="stateMachine">ステートマシン</param>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyIdle::BirdEnemyIdle(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy)
	:
	m_stateMahine{stateMachine}
	,m_birdEnemy{birdEnemy}
	,m_time{}
	,m_attackInterval{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyIdle::~BirdEnemyIdle()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BirdEnemyIdle::Update(const float& deltaTime)
{
	//インターバルを超えたら
	if (m_time >= m_attackInterval)
	{

		//確率
		float ratio = MathUtil::GetRandom<float>(0, 100);


		if (ratio < Params::BIRDENEMY_ATTACK_RATIO)
		{
			//動き状態に
			m_birdEnemy->GetStateMachine()->ChangeState(BirdEnemyState::MOVE);
		}
		else
		{
			//弾攻撃に
			m_birdEnemy->GetStateMachine()->ChangeState(BirdEnemyState::BULLET_ATTACK);

		}
	}


	m_time += deltaTime;

}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyIdle::Enter()
{
	//初期化
	m_time = 0;

	//ランダムでインターバルの作成
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(Params::BIRDENEMY_ACTIONS_MIN_TIME, Params::BIRDENEMY_ACTIONS_MAX_TIME);

	m_attackInterval = dis(gen);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyIdle::Exit()
{
}
