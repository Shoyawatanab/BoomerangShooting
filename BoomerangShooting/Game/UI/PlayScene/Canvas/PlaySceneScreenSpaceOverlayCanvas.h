/*
プレイシーンのカメラの常に移るUiキャンバスクラス
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"
class TargetMarker;


class PlaySceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//ターゲットマーカーの取得
	TargetMarker* GetTargetMarker() { return m_targetMarker; }

public:
	//コンストラクタ
	PlaySceneScreenSpaceOverlayCanvas(Scene* scene,std::vector<Actor*> targets);
	//デストラクタ
	~PlaySceneScreenSpaceOverlayCanvas() override;


	
private:

	TargetMarker* m_targetMarker;

};
