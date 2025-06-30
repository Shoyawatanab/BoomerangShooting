//常に画面に映っているUI用Canvas

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





