/*
	クラス名     : GlobalGameData
	説明         : シーンをまたぐゲームデータ
	補足・注意点 :
*/
#include "pch.h"
#include "GlobalGameData.h"


/// <summary>
/// コンストラク
/// </summary>
GlobalGameData::GlobalGameData()
	:
	m_selectStageNumber{1}
	,m_clearTime{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
GlobalGameData::~GlobalGameData()
{

}
