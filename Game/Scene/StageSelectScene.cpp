/*
	クラス名     : StageSelectScene
	説明         : セレクトシーン
	補足・注意点 :
*/
#include "pch.h"
#include "StageSelectScene.h"
#include "GameBase/Common/Commons.h"

#include "Game/Camera/SelectScene/SelectSceneCamera.h"
#include "Game/Camera/Normal/NormalCamera.h"

#include "Game/UI/SelectScene/Canvas/SelectSceneScreenSpaceOverlayCanvas.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Sound/SelectScene/SelectSceneSound.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
StageSelectScene::StageSelectScene()
	:
	m_camera{}
{
	//FadeManager::GetInstance()->StartFadeOut();
	FadeManager::GetInstance()->StartFadeOut(FadeManager::FadeOutKinds::BOMERANG_FADE_OUT);



}

/// <summary>
/// デストラクタ
/// </summary>
StageSelectScene::~StageSelectScene()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void StageSelectScene::SceneInitialize()
{

	//カメラの作成
	m_camera =AddActor<SelectSceneCamera>(this);

	AddActor<SelectSceneScreenSpaceOverlayCanvas>(this);

	AddActor<SelectSceneSound>(this);

}



