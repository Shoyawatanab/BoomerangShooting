/*
	@file	PlayScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include <cassert>
#include "GameBase/Component/Components.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Player/Player.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/UI/PlayScene/Canvas/PlaySceneScreenSpaceOverlayCanvas.h"
#include "Game/Weapon/WeaponManager.h"
#include "Game/Enemies/EnemyManager.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Effect/EffectFactory.h"
#include "Game/Sound/PlayScene/PlaySceneSound.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラク
/// </summary>
PlayScene::PlayScene()
	:
	m_camera{}
	,m_isChangeScene{}
{
	

	FadeManager::GetInstance()->StartFadeOut();
	
	

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayScene::~PlayScene()
{

	// do nothing.
	//Messenger::GetInstance()->Clear();



}

/// <summary>
/// 初期化
/// </summary>
void PlayScene::Initialize()
{

	using namespace DirectX::SimpleMath;

	//カメラの作成
	m_camera = AddActor<PlaySceneCamera>(this);
	//ステージファクトリー作成
	AddActor<StageFactory>(this);

	//プレイヤ作成	
	auto player = AddActor<Player>(this);

	//武器ファクトリーの生成
	AddActor<WeaponManager>(this, player);

	auto enemyManger = AddActor<EnemyManager>(this, player);

	
	auto ui = AddActor<PlaySceneScreenSpaceOverlayCanvas>(this,enemyManger->GetEnemys());


	//プレイヤの登録
	auto camera = static_cast<PlaySceneCamera*>(m_camera)->SetTarget(player);

	player->SetPlaySceneCamera(camera);
	player->SetTargetMarker(ui->GetTargetMarker());

	AddActor<EffectFactory>(this);

	AddActor<PlaySceneSound>(this);


	//クリアタイムのリセット
	GlobalGameData::GetInstance()->ResetClearTime();

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::SceneUpdate(const float& deltaTime)
{
	
	GlobalGameData::GetInstance()->AddClearTime(deltaTime);


}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::SceneRender()
{
	

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// do nothing.
}




