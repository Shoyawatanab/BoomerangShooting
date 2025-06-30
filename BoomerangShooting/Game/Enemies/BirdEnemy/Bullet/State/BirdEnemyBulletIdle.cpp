#include "pch.h"
#include "BirdEnemyBulletIdle.h"
#include <random>
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="stateMachine">ステートマシン</param>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyBulletIdle::BirdEnemyBulletIdle(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet, BirdEnemy* birdEnemy)
	:
	m_stateMahine{stateMachine}
	,m_bullet{bullet}
	,m_birdEnemy{birdEnemy}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBulletIdle::~BirdEnemyBulletIdle()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BirdEnemyBulletIdle::Update(const float& deltaTime)
{

	UNREFERENCED_PARAMETER(deltaTime);

}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyBulletIdle::Enter()
{
	using namespace DirectX::SimpleMath;
	//親子関係を結ぶ
	m_bullet->GetTransform()->SetParent(m_birdEnemy->GetTransform());
	//親との相対位置のセット
	m_bullet->GetTransform()->SetPosition(Vector3(0, 0, 2));
	
	//非アクティブに
	m_bullet->SetActive(false);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyBulletIdle::Exit()
{
}
