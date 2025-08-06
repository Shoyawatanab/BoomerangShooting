/*
	クラス名     : TitleScene
	説明         : タイトルシーン
	補足・注意点 :
*/
#include "pch.h"
#include "TitleScene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Game/Camera/TitleScene/TitleSceneCamera.h"
#include "Game/UI/TitleScene/Canvas/TitleSceneScreenSpaceOverlayCanvas.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Params.h"
#include "Game/Component/Components.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Sound/TitleScene/TitleSceneSound.h"


/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
	:
	m_camera{}
{

	//FadeManager::GetInstance()->StartFadeOut();

	FadeManager::GetInstance()->StartFadeOut(FadeManager::FadeOutKinds::BOMERANG_FADE_OUT);

}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::SceneInitialize()
{


	//カメラの作成
	m_camera = AddActor<TitleSceneCamera>(this);

	//ステージファクトリー作成
	AddActor<StageFactory>(this);


	//モデルの作成
	auto model = AddActor<PlayerModel>(this);
	//モデルの大きさをプレイヤの設定に
	model->GetTransform()->SetScale(Params::PLAYER_SCALE);
	model->GetTransform()->Translate(PLAYER_POSITION);
	model->GetTransform()->SetRotate(Params::PLAYER_ROTATION);

	AddActor<TitleSceneScreenSpaceOverlayCanvas>(this);

	//カメラのターゲットのセット
	m_camera->SetTargetPosition(model->GetTransform()->GetPosition() );


	AddActor<TitleSceneSound>(this);




}


