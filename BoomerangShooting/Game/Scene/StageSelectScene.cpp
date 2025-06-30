/*
	@file	StageSelectScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "StageSelectScene.h"
#include "GameBase/Common/Commons.h"

#include "Game/Camera/SelectScene/SelectSceneCamera.h"
#include "Game/Camera/Normal/NormalCamera.h"

#include "Game/UI/SelectScene/Canvas/SelectSceneScreenSpaceOverlayCanvas.h"
#include "Game/Fade/FadeManager.h"


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
StageSelectScene::StageSelectScene(SceneManager* sceneManager)
	:
	m_camera{}
{
	FadeManager::GetInstance()->StartFadeOut();

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
StageSelectScene::~StageSelectScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void StageSelectScene::Initialize()
{

	//カメラの作成
	m_camera =AddActor<SelectSceneCamera>(this);

	auto ui = AddActor<SelectSceneScreenSpaceOverlayCanvas>(this);


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void StageSelectScene::SceneUpdate(const float& deltaTime)
{

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void StageSelectScene::SceneRender()
{

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void StageSelectScene::Finalize()
{
	// do nothing.
}

