/*
	@file	BossBeamAttackEnd.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackEnd.h"
#include "GameBase/Common/Commons.h"
#include "Game/MathUtil.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"
#include "Game/Enemies/BossEnemy/Beam/Rays/BossEnemyBeamRays.h"
#include "GameBase/Component/Components.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="bossenemy">所有者</param>
/// <param name="beam">ビーム</param>
/// <param name="beamAttack">ビーム攻撃</param>
BossBeamAttackEnd::BossBeamAttackEnd(Actor* bossenemy
	, BossEnemyBeam* beam
	, BossBeamAttackActionController* beamAttack)
	:
	m_commonResources{}
	, m_bossEnemy{ bossenemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
	,m_time{}
	,m_initalScale{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackEnd::~BossBeamAttackEnd()
{
	// do nothing.
}



/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
BossBeamAttackEnd::ActionState BossBeamAttackEnd::Update(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	//進行割合を求める
	float ratio = m_time / Params::BOSSENEMY_BEAM_SHRINK_TIME;
	//1.0を超えないように
	ratio = std::min(ratio, 1.0f);
	//大きさの取得
	Vector3 scale = m_beam->GetTransform()->GetScale();
	//進行割合に応じた大きさ
	scale.x = MathUtil::Lerp(m_initalScale.x, 0.0f, ratio);
	scale.y = MathUtil::Lerp(m_initalScale.y, 0.0f, ratio);
	//大きさのセット
	m_beam->GetTransform()->SetScale(scale);


	m_time += deltaTime;

	m_time = std::min(m_time, END_TIME);


	if (m_time == END_TIME)
	{
		//終了
		return ActionState::END;
	}

	//実行中
	return ActionState::RUNNING;

}


/// <summary>
/// 状態に入った時
/// </summary>
void BossBeamAttackEnd::Enter()
{
	m_time = 0;
	m_initalScale = m_beam->GetTransform()->GetScale();
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BossBeamAttackEnd::Exit()
{
	m_beam->GetTransform()->SetScale(DirectX::SimpleMath::Vector3::One);
	m_beam->SetActive(false);
}





