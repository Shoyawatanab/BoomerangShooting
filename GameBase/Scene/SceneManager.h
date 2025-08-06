/*
	クラス名     : SceneManager
	説明         : シーンマネージャー
	補足・注意点 :　シーンの作成時のクラスとSceneIDはゲームごとのクラスを使用すること

*/
#pragma once

// 前方宣言
class Scene;
class FadeManager;

class SceneManager 
{
public:
	// シーンID ゲームごとにカスタムする
	enum class SceneID : unsigned int
	{
		NONE = 0,
		TITLE,
		PLAY,
		STAGESELECT,
		RESULT
	};

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
	//フェードマネージャー
	FadeManager* m_fadeManager;

};
