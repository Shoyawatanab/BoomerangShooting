/*
	@file	WalkActionComtroller.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "WalkActionComtroller.h"
#include "Game/Enemies/BossEnemy/Action/Walk/WalkActionComtroller.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
WalkActionComtroller::WalkActionComtroller(BossEnemy* own
	, Actor* target)
	:
	m_own{own}
	,m_target{target}
{
	//各状態の作成
	m_walkingAction = std::make_unique<WalkAction>(m_own,m_target);
	m_orientation = std::make_unique<OrientationAction>(m_own, m_target);

	//動作順に追加
	AddAction({
		m_walkingAction.get() 
		});

}

/// <summary>
/// デストラクタ
/// </summary>
WalkActionComtroller::~WalkActionComtroller()
{
	// do nothing.
}


