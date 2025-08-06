/*
	クラス名     : ScreenSpaceOverlayCanvas
	説明         : 常に画面に映っているUI用Canvas
	補足・注意点 :
*/
#include "pch.h"
#include "ScreenSpaceOverlayCanvas.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
ScreenSpaceOverlayCanvas::ScreenSpaceOverlayCanvas(Scene* scene)
	:
	Canvas(scene,RenderType::SpaceOverlay)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ScreenSpaceOverlayCanvas::~ScreenSpaceOverlayCanvas()
{
}
