/*
	クラス名     : BossDeathActionController
	説明         : ボス敵の倒したときのコントローラー
	補足・注意点 :
*/
#include "pch.h"
#include "BossDeathActionController.h"
#include "GameBase/Common/Commons.h"
#include "Game/Enemies/BossEnemy/Action/Death/BossDeathAction.h"
#include "Game/Enemies/BossEnemy/Action/Death/BossDeathEndAction.h"




/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
BossDeathActionController::BossDeathActionController(BossEnemy* bossEnemy)
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
BossDeathActionController::~BossDeathActionController()
{
	// do nothing.
}


