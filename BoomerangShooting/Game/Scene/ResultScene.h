/*
	@file	ResultScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "Game/Scene/SceneManager.h"

// 前方宣言
class CommonResources;





class ResultScene  :  public Scene
{

public:
    Camera* GetCamera() const  override { return m_camera; };


public:
    ResultScene();
    ~ResultScene() override;

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
