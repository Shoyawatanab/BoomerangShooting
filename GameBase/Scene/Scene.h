/*
	クラス名     : Scene
	説明         : すべてのシーンの基底クラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Scene/SceneManager.h"

class Actor;
class CommonResources;
class RenderManager;
class CollisionManager;
class RigidbodyManager;
class Camera;
class UIManager;

class Scene
{
public:
	//切り替えシーンIDの取得
	SceneManager::SceneID GetNextSceneID() { return m_nextSceneID; }

	//マネージャーの取得
	RenderManager* GetRenderMangaer() { return m_renderMangaer.get(); }
	CollisionManager* GetCollisionManager() { return m_collisionManager.get(); }
	RigidbodyManager* GetRigidbodyManager() { return m_rigidbodyManager.get(); }
	UIManager* GetUIManager() { return m_uiManager.get(); }

	//カメラの取得
	virtual Camera* GetCamera() const = 0;

public:

	// コンストラクタ、デストラクタ
	Scene();
	virtual ~Scene();
	// 初期化
	void Initialize();
	// 派生クラス初期化
	virtual void SceneInitialize() = 0;
	// 更新処理
	void Update(float deltaTime);
	// 派生クラス更新処理
	virtual void SceneUpdate(const float& deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };
	// 描画処理
	void Render();
	virtual void SceneRender() {};
	// 終了処理
	virtual void Finalize() {};
	
	// アクター削除フラグをオンにする
	void ActorDestroyOn() { m_isActorDestroy = true; }

	// アクター追加
	template<typename Act , typename...Args>
	Act* AddActor(Args&&... args);
	// アクター削除
	void RemoveActor();

	//シーン切り替え
	void ChangeScene(SceneManager::SceneID sceneID);

private:
	// チェンジフラグ
	bool m_isChangeScene;
	// 管理アクター
	std::vector<std::unique_ptr<Actor>> m_actors;
	// 保留アクター
	std::vector<std::unique_ptr<Actor>> m_holdActors;
	// アップデート確認用フラグ
	bool m_updateNow;
	// アクター削除フラグ
	bool m_isActorDestroy;
	//次のシーンID
	SceneManager::SceneID m_nextSceneID;
	// キーボードステート
	DirectX::Keyboard::State m_keyboardState;

	//描画のマネージャー
	std::unique_ptr<RenderManager> m_renderMangaer;
	//当たり判定のマネージャー
	std::unique_ptr<CollisionManager> m_collisionManager;
	//リジットボディーマネージャー
	std::unique_ptr<RigidbodyManager> m_rigidbodyManager;
	//UIマネージャー
	std::unique_ptr<UIManager> m_uiManager;



};

template<typename Act , typename...Args>
inline Act* Scene::AddActor(Args&&...args)
{
	// アクターの生成
	auto actor = std::make_unique<Act>(std::forward<Args>(args)...);
	// 戻り値
	Act* act = actor.get();
	// アップデート中の場合
	if (m_updateNow)
	{
		m_holdActors.push_back(std::move(actor));
	}
	else
	{
		m_actors.push_back(std::move(actor));
	}
	return act;
}

