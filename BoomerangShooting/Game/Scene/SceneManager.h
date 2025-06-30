/*
	@file	SceneManager.h
	@brief	シーンマネージャクラス
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Global/GlobalMeesageType.h"

// 前方宣言
class FadeManager;

class SceneManager : public IObserver<GlobalMessageType>
{
public:

	// シーンID
	enum class SceneID : unsigned int
	{
		NONE,
		TITLE,
		PLAY,
		STAGESELECT,
		RESULT
	};

	enum StageID
	{
		STAGE1 = 0,
		STAGE2

	};
public:

	//次のシーンのIDのセット
	void SetNextSceneID(SceneID sceneID) { m_nextSceneID =  sceneID; }

public:
	//コンストラク
	SceneManager();
	//デストラクタ
	~SceneManager();
	//初期化
	void Initialize();
	//更新処理
	void Update(float elapsedTime);
	//描画
	void Render();
	//
	void Finalize();

	//通知時に呼び出される
	void Notify(GlobalMessageType type, void* datas) override;



private:
	//シーン切り替え
	void ChangeScene(SceneID sceneID);
	//シーンの作成
	void CreateScene(SceneID sceneID);
	//シーンの削除
	void DeleteScene();

private:
	//実行シーン
	std::unique_ptr<Scene> m_currentScene;
	//次のシーン
	SceneID m_nextSceneID;

	//フェードマネージャー
	FadeManager* m_fadeManager;

};
