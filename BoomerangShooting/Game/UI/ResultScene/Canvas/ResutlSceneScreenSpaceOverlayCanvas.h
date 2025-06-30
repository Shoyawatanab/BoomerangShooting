#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class ResutlSceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//コンストラクタ
	ResutlSceneScreenSpaceOverlayCanvas(Scene* scene);
	//デストラクタ
	~ResutlSceneScreenSpaceOverlayCanvas() override;

};
