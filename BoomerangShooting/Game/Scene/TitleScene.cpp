/*
	@file	TitleScene.cpp
	@brief	タイトルシーンクラス
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
#include "GameBase/Component/Components.h"
#include "Game/Fade/FadeManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
	:
	m_projection{}
{

	FadeManager::GetInstance()->StartFadeOut();



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
void TitleScene::Initialize()
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

	auto ui = AddActor<TitleSceneScreenSpaceOverlayCanvas>(this);

	//カメラのターゲットのセット
	m_camera->SetTargetPosition(model->GetTransform()->GetPosition() );




	//// シーン変更フラグを初期化する
	//m_isChangeScene = false;

	////フェードアウトの開始
	//CommonResources::GetInstance()->GetFade()->StartNormalFadeOut();

	//ShowCursor(true);



}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleScene::SceneUpdate(const float& deltaTime)
{
	// 宣言をしたが、実際は使用していない変数
	UNREFERENCED_PARAMETER(deltaTime);






}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleScene::SceneRender()
{




	////// デバッグ情報を表示する
	//auto debugString = m_commonResources->GetDebugString();
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().x);
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().y);
	//debugString->AddString("X %d" , m_commonResources->GetDeviceResources()->GetOutputSize().right);
	//debugString->AddString("Y %d" , m_commonResources->GetDeviceResources()->GetOutputSize().bottom);


}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TitleScene::Finalize()
{
	// do nothing.
}



void TitleScene::CreateTextures()
{


}
