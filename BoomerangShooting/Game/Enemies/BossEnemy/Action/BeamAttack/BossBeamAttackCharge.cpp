/*
	@file	BossBeamAttackCharge.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackCharge.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossBeamAttackCharge::BossBeamAttackCharge(BossEnemy* bossenemy
	, BossEnemyBeam* beam
	, BossBeamAttackActionController* beamAttack)
	:
	m_commonResources{}
	,m_bossEnemy{bossenemy}
	,m_beam{beam}
	,m_particleCreateTime{}
	,m_time{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackCharge::~BossBeamAttackCharge()
{
	// do nothing.
}



/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossBeamAttackCharge::ActionState BossBeamAttackCharge::Update(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	//進行割合を求める
	float ratio = m_time / Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME;

	ratio = std::min(ratio, 1.0f);

	////サイズの補間
	Vector3 scale = Vector3::Lerp(Vector3::Zero, Params::BOSSENEMY_BEAM_BALL_MAX_SCALE, ratio);

	m_beam->GetEnergyBall()->GetTransform()->SetScale(scale);

	m_time += deltaTime;

	m_bossEnemy->Rotation(deltaTime);
	

	if (m_time > Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME)
	{
		return ActionState::END;

	}


	return ActionState::RUNNING;

}


void BossBeamAttackCharge::Enter()
{
	using namespace DirectX::SimpleMath;

	m_time = 0;
	//ボールの有効
	m_beam->GetEnergyBall()->SetActive(true);
	//初期の大きさをゼロに
	m_beam->GetEnergyBall()->GetTransform()->SetScale(Vector3::Zero);


}


void BossBeamAttackCharge::Exit()
{


}



