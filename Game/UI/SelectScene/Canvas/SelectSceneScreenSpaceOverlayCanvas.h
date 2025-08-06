/*
	クラス名     : SelectSceneScreenSpaceOverlayCanvas
	説明         : セレクトシーンの常に映り続けるUIキャンバスI
	補足・注意点 :
*/
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
