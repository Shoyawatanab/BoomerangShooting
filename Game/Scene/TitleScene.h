/*
    クラス名     : TitleScene
    説明         : タイトルシーン
    補足・注意点 :
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include <unordered_map>




class TitleScene :  public Scene
{

private:


    static constexpr DirectX::SimpleMath::Vector3 PLAYER_POSITION {0.0f,0.8f,0.0f};



public:
    //カメラの取得
    Camera* GetCamera() const  override { return m_camera; };


public:
    //コンストラク 
    TitleScene();
    //デストラクタ
    ~TitleScene() override;
    //初期化
    void SceneInitialize() override;
private:
    //カメラ
    Camera* m_camera;


};
