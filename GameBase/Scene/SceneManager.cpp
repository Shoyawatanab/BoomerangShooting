/*
	クラス名     : SceneManager
	説明         : シーンマネージャー
	補足・注意点 :　シーンの作成時のクラスとSceneIDはゲームごとのクラスを使用すること
*/
#include "pch.h"
#include "SceneManager.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"


//ゲームごとのシーン
#include "Game/Scene/TitleScene.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Scene/ResultScene.h"
#include "Game/Scene/StageSelectScene.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene{}
	,m_fadeManager{}
{

	m_fadeManager = FadeManager::GetInstance();


}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	Finalize();
}

/// <summary>
/// 初期化
/// </summary>
void SceneManager::Initialize()
{

	//初期シーン
	ChangeScene(SceneID::TITLE);

}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void SceneManager::Update(float elapsedTime)
{
	//シーンの更新
	m_currentScene->Update(elapsedTime);

	//シーンIDの取得
	auto nextSceneID = m_currentScene->GetNextSceneID();

	// シーンを変更しないとき
	if (nextSceneID == SceneID::NONE) return;

	//フェード
	if (m_fadeManager->GetFadeState() != FadeManager::FadeState::NONE)
	{
		return;
	}

	//シーン切り替え
	ChangeScene(nextSceneID);
	
}

/// <summary>
/// 描画
/// </summary>
void SceneManager::Render()
{
	//シーンの描画
	m_currentScene->Render();
}


/// <summary>
/// 後始末
/// </summary>
void SceneManager::Finalize()
{
	//シーンの削除
	DeleteScene();
}


/// <summary>
/// シーン変更
/// </summary>
/// <param name="sceneID"></param>
void SceneManager::ChangeScene(SceneID sceneID)
{
	//シーンの削除
	DeleteScene();
	//シーンの作成
	CreateScene(sceneID);
}

/// <summary>
/// シーンの作成
/// </summary>
/// <param name="sceneID"></param>
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
			m_currentScene = std::make_unique<StageSelectScene>();
			break;
		case SceneID::RESULT:
			m_currentScene = std::make_unique<ResultScene>();
			break;
		default:
			assert(!"SceneManager::CreateScene::シーン名が存在しません！");
	}

	assert(m_currentScene && "SceneManager::CreateScene::次のシーンが生成されませんでした！");
	m_currentScene->Initialize();

}


/// <summary>
/// シーンの削除
/// </summary>
void SceneManager::DeleteScene()
{
	if (m_currentScene)
	{
		m_currentScene.reset();
	}
}






