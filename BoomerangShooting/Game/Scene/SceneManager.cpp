/*
	@file	SceneManager.cpp
	@brief	シーンマネージャクラス
*/
#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "StageSelectScene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
SceneManager::SceneManager()
	:
	m_currentScene{}
	,m_nextSceneID{}
	,m_fadeManager{}
{

	m_fadeManager = FadeManager::GetInstance();

	GlobalMessenger::GetInstance()->Rigister(
		{
			GlobalMessageType::CHANGE_TITLE_SCENE
			,GlobalMessageType::CHANGE_SELECT_SCENE
			,GlobalMessageType::CHANGE_PLAY_SCENE
			,GlobalMessageType::CHANGE_RESULT_SCENE
		}, this
	);

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
SceneManager::~SceneManager()
{
	Finalize();
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void SceneManager::Initialize()
{

	//初期シーン
	ChangeScene(SceneID::PLAY);



}


//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void SceneManager::Update(float elapsedTime)
{
	m_currentScene->Update(elapsedTime);

	// シーンを変更しないとき
	if (m_nextSceneID == SceneID::NONE) return;

	//フェード
	if (m_fadeManager->GetFadeState() != FadeManager::FadeState::FADE_IN_END)
	{
		return;
	}

	//シーン切り替え
	ChangeScene(m_nextSceneID);
	//初期化
	m_nextSceneID = SceneID::NONE;
	
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void SceneManager::Render()
{
	m_currentScene->Render();
}


//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void SceneManager::Finalize()
{
	DeleteScene();
}


//---------------------------------------------------------
// シーンを変更する
//---------------------------------------------------------
void SceneManager::ChangeScene(SceneID sceneID)
{
	DeleteScene();
	CreateScene(sceneID);
}

//---------------------------------------------------------
// シーンを作成する
//---------------------------------------------------------
void SceneManager::CreateScene(SceneID sceneID)
{
	assert(m_currentScene == nullptr);

	switch (sceneID)
	{
		case SceneID::TITLE:
			m_currentScene = std::make_unique<TitleScene>();
			break;
		case SceneID::PLAY:
			m_currentScene = std::make_unique<PlayScene>();
			break;
		case SceneID::STAGESELECT:
			m_currentScene = std::make_unique<StageSelectScene>(this);
			break;
		case SceneID::RESULT:
			m_currentScene = std::make_unique<ResultScene>();
			break;
		default:
			assert(!"SceneManager::CreateScene::シーン名が存在しません！");
			// no break
	}

	assert(m_currentScene && "SceneManager::CreateScene::次のシーンが生成されませんでした！");
	m_currentScene->Initialize();

}

//---------------------------------------------------------
// シーンを削除する
//---------------------------------------------------------
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
		//メッセンジャーもクリア
		SceneMessenger::GetInstance()->Clear();

	}

}



/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void SceneManager::Notify(GlobalMessageType type, void* datas)
{
	switch (type)
	{
		case GlobalMessageType::CHANGE_TITLE_SCENE:
			SetNextSceneID(SceneID::TITLE);
			break;
		case GlobalMessageType::CHANGE_SELECT_SCENE:
			SetNextSceneID(SceneID::STAGESELECT);
			break;
		case GlobalMessageType::CHANGE_PLAY_SCENE:
			SetNextSceneID(SceneID::PLAY);
			break;
		case GlobalMessageType::CHANGE_RESULT_SCENE:
			SetNextSceneID(SceneID::RESULT);
			break;
		default:
			break;
	}
}



