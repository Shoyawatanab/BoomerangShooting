#include "pch.h"
#include "BirdEnemyMove.h"
#include <cmath>
#include <random>
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
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
BirdEnemyMove::BirdEnemyMove(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy)
	:
	m_stateMahine{ stateMachine }
	, m_birdEnemy{ birdEnemy }
	,m_time{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyMove::~BirdEnemyMove()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BirdEnemyMove::Update(const float& deltaTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_time = std::min(m_time, Params::BIRDENEMY_MOVE_TIME);

	float ratio = m_time / Params::BIRDENEMY_MOVE_TIME;

	ratio = std::min(ratio, 1.0f);

	DirectX::SimpleMath::Vector3 pos = Vector3::Lerp(m_startPosition, m_endPosition, ratio);

	auto transform = m_birdEnemy->GetTransform();

	transform->SetPosition(pos);

	//transform->Rotate(elapsedTime);


	m_time += deltaTime;

	if (ratio == 1.0f)
	{

		m_birdEnemy->GetStateMachine()->ChangeState(BirdEnemyState::IDEL);

	}

}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyMove::Enter()
{

	//初期化
	m_startPosition = m_birdEnemy->GetTransform()->GetWorldPosition();
	m_time = 0;

	// ランダムな角度を生成
	float angle = MathUtil::GetRandom(0.0f, DirectX::XM_2PI);

	//移動変数
	DirectX::SimpleMath::Vector3 offsetPosition;
	offsetPosition.x = Params::BIRDENEMY_MOVE_RADIUS * cos(angle);
	offsetPosition.y = Params::BIRDENEMY_MOVE_RADIUS * sin(angle);


	//終わりの座標を求める
	m_endPosition = m_startPosition + offsetPosition;


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyMove::Exit()
{
}
