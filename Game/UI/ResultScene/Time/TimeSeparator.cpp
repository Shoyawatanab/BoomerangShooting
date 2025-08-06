/*
	クラス名     : TimeSeparator
	説明         : リザルトシーンの時間UIの分と秒の間の点のUI
	補足・注意点 :
*/
#include "pch.h"
#include "TimeSeparator.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas"></param>
TimeSeparator::TimeSeparator(Canvas* canvas)
	:
	Image(canvas,"Ten")
{

	GetTransform()->SetScale(SCALE);

}

/// <summary>
/// デストラクタ
/// </summary>
TimeSeparator::~TimeSeparator()
{
}


