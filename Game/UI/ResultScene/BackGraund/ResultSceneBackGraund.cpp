/*
	クラス名     : ResultSceneBackGraund
	説明         : リザルトシーンの背景UI
	補足・注意点 :
*/
#include "pch.h"
#include "ResultSceneBackGraund.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
ResultSceneBackGraund::ResultSceneBackGraund(Canvas* canvas)
	:
	Image(canvas, "ClearBackGraund")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITION);

}

ResultSceneBackGraund::~ResultSceneBackGraund()
{
}
