/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "SceneManager.h"

// 前方宣言

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class CameraManager;
}

class PlayScene  :  public Scene// ,public IObserver<GamePlayMessageType>
{
public:

	Camera* GetCamera() const  override { return m_camera; };


public:
	//コンストラクタ
	PlayScene();
	//デストラクタ
	~PlayScene() override;

	void Initialize() override;

	void SceneUpdate(const float& deltaTime)override;

	void SceneRender() override;

	void Finalize() override;
	

private:


	// シーンチェンジフラグ
	bool m_isChangeScene;
	//カメラ
	Camera* m_camera;



};
