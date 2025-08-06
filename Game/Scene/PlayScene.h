/*
	クラス名     : PlayScene
	説明         : プレイシーン
	補足・注意点 :
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "GameBase/Scene/SceneManager.h"

class PickUpManager;


class PlayScene  :  public Scene
{
public:
	//カメラの取得
	Camera* GetCamera() const  override { return m_camera; };
	//回収マネージャーの取得
	PickUpManager* GetPickUpManager() { return m_pickUpManager.get(); }


public:
	//コンストラクタ
	PlayScene();
	//デストラクタ
	~PlayScene() override;

	void SceneInitialize() override;

	void SceneUpdate(const float& deltaTime)override;


private:


	//カメラ
	Camera* m_camera;
	//回収マネージャー
	std::unique_ptr<PickUpManager> m_pickUpManager;
	//プレイ時間
	float m_playTime;

};
