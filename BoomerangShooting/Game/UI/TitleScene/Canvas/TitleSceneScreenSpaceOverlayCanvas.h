#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class TitleSceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//コンストラクタ
	TitleSceneScreenSpaceOverlayCanvas(Scene* scene);
	//デストラクタ
	~TitleSceneScreenSpaceOverlayCanvas() override;

};
