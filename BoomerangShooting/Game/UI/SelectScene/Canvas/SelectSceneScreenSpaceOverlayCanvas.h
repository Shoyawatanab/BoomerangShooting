#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class SelectSceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//コンストラクタ
	SelectSceneScreenSpaceOverlayCanvas(Scene* scene);
	//デストラクタ
	~SelectSceneScreenSpaceOverlayCanvas() override;

};
