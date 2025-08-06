/*
	クラス名     : ScreenSpaceOverlayCanvas
	説明         : 常に画面に映っているUI用Canvas
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Canvas/Canvas.h"

class ScreenSpaceOverlayCanvas : public Canvas
{
public:
	//コンストラクタ
	ScreenSpaceOverlayCanvas(Scene* scene);
	//デストラクタ
	~ScreenSpaceOverlayCanvas();

};





