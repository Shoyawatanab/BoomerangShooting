/*
	@file	ResultScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "ResultScene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Component/Components.h"
#include "Game/Camera/Result/ResultCamera.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Params.h"
#include "Game/UI/ResultScene/Canvas/ResutlSceneScreenSpaceOverlayCanvas.h"


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ResultScene::ResultScene()
	:
	m_isChangeScene{}
	,m_camera{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
ResultScene::~ResultScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void ResultScene::Initialize()
{

	using namespace DirectX::SimpleMath;
	//ステージファクトリー作成
	AddActor<StageFactory>(this);

	//カメラの作成
	m_camera = AddActor<ResultCamera>(this);

	auto ui = AddActor<ResutlSceneScreenSpaceOverlayCanvas>(this);


	//モデルの作成
	auto model = AddActor<PlayerModel>(this);
	//モデルの大きさをプレイヤの設定に
	model->GetTransform()->SetScale(Params::PLAYER_SCALE);
	model->GetTransform()->Translate(DirectX::SimpleMath::Vector3(-1.8f,0.5f,0));
	model->GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(25),0,0));


	FadeManager::GetInstance()->StartFadeOut();


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultScene::SceneUpdate(const float& deltaTime)
{


}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultScene::SceneRender()
{


}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ResultScene::Finalize()
{
	// do nothing.
}


