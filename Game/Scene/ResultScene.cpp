/*
	クラス名     : ResultScene
	説明         : リザルトシーン
	補足・注意点 :
*/
#include "pch.h"
#include "ResultScene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Game/Component/Components.h"
#include "Game/Camera/Result/ResultCamera.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Params.h"
#include "Game/UI/ResultScene/Canvas/ResutlSceneScreenSpaceOverlayCanvas.h"


#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
	:
	m_isChangeScene{}
	,m_camera{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void ResultScene::SceneInitialize()
{

	using namespace DirectX::SimpleMath;
	//ステージファクトリー作成
	AddActor<StageFactory>(this);

	//カメラの作成
	m_camera = AddActor<ResultCamera>(this);

	AddActor<ResutlSceneScreenSpaceOverlayCanvas>(this);


	//モデルの作成
	auto model = AddActor<PlayerModel>(this);
	//モデルの大きさをプレイヤの設定に
	model->GetTransform()->SetScale(Params::PLAYER_SCALE);
	model->GetTransform()->Translate(DirectX::SimpleMath::Vector3(-1.8f,0.5f,0));
	model->GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(25),0,0));


	FadeManager::GetInstance()->StartFadeOut();

	GlobalGameData::GetInstance()->SetClearTime(198);

}



