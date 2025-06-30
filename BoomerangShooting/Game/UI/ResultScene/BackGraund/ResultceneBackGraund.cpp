#include "pch.h"
#include "ResultSceneBackGraund.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
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
