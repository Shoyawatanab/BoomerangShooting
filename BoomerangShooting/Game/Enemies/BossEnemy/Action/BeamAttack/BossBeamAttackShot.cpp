/*
	@file	BossBeamAttackShot.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackShot.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Player/Player.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"
#include "Game/Enemies/BossEnemy/Beam/Rays/BossEnemyBeamRays.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="bossEnemy">所有者</param>
/// <param name="beam">ビーム</param>
/// <param name="beamAttack">ビーム攻撃</param>
/// <param name="player">プレイヤ</param>
BossBeamAttackShot::BossBeamAttackShot(Actor* bossEnemy
	, BossEnemyBeam* beam
	, BossBeamAttackActionController* beamAttack
	, Actor* player)
	:
	m_bossEnemy{ bossEnemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
	,m_player{player}
	,m_moveDirection{DirectX::SimpleMath::Vector3::Backward}
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackShot::~BossBeamAttackShot()
{
	// do nothing.
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossBeamAttackShot::ActionState BossBeamAttackShot::Update(const float& deltaTime)
{

	using namespace DirectX::SimpleMath;
	//ボールの取得
	auto ball = m_beam->GetEnergyBall();
	//ボールの座標を＋Z方向に移動
	ball->GetTransform()->SetPosition(ball->GetTransform()->GetPosition() + m_moveDirection * deltaTime * SHOT_SPEED);
	//光線の取得
	auto rays = m_beam->GetRays();
	//光線の大きさの取得
	auto raysScale = rays->GetTransform()->GetScale();
	//ビーム全体とボールの距離を求める
	float distaance = Vector3::Distance(m_beam->GetTransform()->GetWorldPosition() , ball->GetTransform()->GetWorldPosition());
	//ｚ座標を距離にする
	raysScale.z = distaance;
	//光線の大きさのセット
	rays->GetTransform()->SetScale(raysScale);

	//実行中　　　弾が当たった時に状態を切り替える
	return ActionState::RUNNING;

}

/// <summary>
/// 状態に入った時
/// </summary>
void BossBeamAttackShot::Enter()
{


	//光線の取得
	auto rays = m_beam->GetRays();
	//光線の初期の大きさのセット
	rays->GetTransform()->SetScale(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE);
	//光線を有効
	m_beam->GetRays()->SetActive(true);

	//ビーム全体をターゲット方向に回転
	m_beam->TargetToRotation();
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BossBeamAttackShot::Exit()
{

	m_beam->GetEnergyBall()->GetComponent<AABB>()->SetActive(false);

}

