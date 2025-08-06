/*
	クラス名     : PlaySceneScreenSpaceOverlayCanvas
	説明         : プレイシーンの常に画面に移るUIキャンバス
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"
#include "Game/Messenger/Messengers.h"

class TargetMarker;
class PickUpUI;

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

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) ;


private:

	//ステージごとのUI
	void StageUI();

	
private:
	//ターゲットマーカーUI
	TargetMarker* m_targetMarker;
	//回収UI
	PickUpUI* m_pickUpUI;
};
