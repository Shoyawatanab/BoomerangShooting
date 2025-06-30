/*
	@file	TitleScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include <unordered_map>
#include "Libraries/WataLib/UserInterface.h"




class TitleScene :  public Scene
{

private:


    static constexpr DirectX::SimpleMath::Vector3 PLAYER_POSITION {0.0f,0.8f,0.0f};



public:
    Camera* GetCamera() const  override { return m_camera; };


public:
    TitleScene();
    ~TitleScene() override;


private:



public:
    void Initialize() override;
    void SceneUpdate(const float& deltaTime)override;
    void SceneRender() override;
    void Finalize() override;

    void CreateTextures();

private:

    Camera* m_camera;


    // 射影行列
    DirectX::SimpleMath::Matrix m_projection;


    // シーンチェンジフラグ
    bool m_isChangeScene;


};
