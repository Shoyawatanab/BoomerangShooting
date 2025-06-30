/*
	@file	BossDeathActionComtroller.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossDeathActionComtroller.h"
#include "GameBase/Common/Commons.h"
#include "Game/Enemies/BossEnemy/Action/Death/BossDeathAction.h"
#include "Game/Enemies/BossEnemy/Action/Death/BossDeathEndAction.h"




/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
BossDeathActionComtroller::BossDeathActionComtroller(BossEnemy* bossEnemy)
{

	m_idle = std::make_unique<BossDeathAction>();
	m_end = std::make_unique<BossDeathEndAction>(bossEnemy);

	AddAction(
		{
			m_idle.get()
			,m_end.get()
		}
	);

}

/// <summary>
/// デストラクタ
/// </summary>
BossDeathActionComtroller::~BossDeathActionComtroller()
{
	// do nothing.
}


