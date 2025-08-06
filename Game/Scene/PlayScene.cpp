/*
	クラス名     : PlayScene
	説明         : プレイシーン
	補足・注意点 :
*/
#include "pch.h"
#include "PlayScene.h"
#include <cassert>
#include "Game/Component/Components.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Player/Player.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"
#include "Game/UI/PlayScene/Canvas/PlaySceneScreenSpaceOverlayCanvas.h"
#include "Game/Weapon/WeaponManager.h"
#include "Game/Enemies/EnemyManager.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Effect/EffectFactory.h"
#include "Game/Sound/PlayScene/PlaySceneSound.h"
#include "Game/GlobalGameData.h"
#include "Game/Manager/Managers.h"

/// <summary>
/// コンストラク
/// </summary>
PlayScene::PlayScene()
	:
	m_camera{}
	,m_pickUpManager{}
	,m_playTime{}
{
	
	m_pickUpManager = std::make_unique<PickUpManager>();

	//
	FadeManager::GetInstance()->StartFadeOut();

}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{

	//プレイ時間のセット
	GlobalGameData::GetInstance()->SetClearTime(m_playTime);


}

/// <summary>
/// 初期化
/// </summary>
void PlayScene::SceneInitialize()
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

	
	auto ui = AddActor<PlaySceneScreenSpaceOverlayCanvas>(this,enemyManger->GetTargets());


	//プレイヤの登録
	auto camera = static_cast<PlaySceneCamera*>(m_camera)->SetTarget(player);

	player->SetPlaySceneCamera(camera);
	player->SetTargetMarker(ui->GetTargetMarker());

	AddActor<EffectFactory>(this);

	AddActor<PlaySceneSound>(this);


	//クリアタイムのリセット
	GlobalGameData::GetInstance()->ResetClearTime();



}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::SceneUpdate(const float& deltaTime)
{
	
	m_pickUpManager->Update(deltaTime);


	m_playTime += deltaTime;

}






