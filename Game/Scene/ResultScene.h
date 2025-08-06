/*
    クラス名     : ResultScene
    説明         : リザルトシーン
    補足・注意点 :
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "GameBase/Scene/SceneManager.h"

// 前方宣言
class CommonResources;

class ResultScene  :  public Scene
{

public:
    //カメラの取得
    Camera* GetCamera() const  override { return m_camera; };


public:
    //コンストラクタ
    ResultScene();
    //デストラクタ
    ~ResultScene() override;
    //初期化
    void SceneInitialize() override;

private:

	// シーンチェンジフラグ
	bool m_isChangeScene;
    //カメラ
    Camera* m_camera;

};
