/*
	@file	BossBeam.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeam.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Enemies/BossEnemy/BossBeam/BossBeamEnergyBall.h"
#include "Game/Enemies/BossEnemy/BossBeam/BossBeamRays.h"
#include "Game/Params.h"
#include "Game/Player/Player.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossBeam::BossBeam(Scene* scene)
	:
	Actor(scene)
	,m_energyBall{}
	,m_preliminaryActitonTime{}
	,m_rays{}
{
	
	//m_energyBall = std::make_unique<BossBeamEnergyBall>(this);
	//m_rays = std::make_unique<BossBeamRays>(this);


}

/// <summary>
/// デストラクタ
/// </summary>
BossBeam::~BossBeam()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void BossBeam::Initialize()
{



	
}

void BossBeam::UpdateActor(const float& deltatime)
{
}









