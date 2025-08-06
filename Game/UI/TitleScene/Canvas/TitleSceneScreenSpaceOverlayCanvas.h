/*
	クラス名     : TitleSceneScreenSpaceOverlayCanvas
	説明         : タイトルシーンの常に映り続けるUIキャンバス
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"


class TitleSceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:

	static constexpr DirectX::SimpleMath::Vector3 LOGO_POSITION{390, 120, 0};

	static constexpr DirectX::SimpleMath::Vector3 LOGO_SCALE{0.25, 0.25, 0};


public:
	//コンストラクタ
	TitleSceneScreenSpaceOverlayCanvas(Scene* scene);
	//デストラクタ
	~TitleSceneScreenSpaceOverlayCanvas() override;

};
