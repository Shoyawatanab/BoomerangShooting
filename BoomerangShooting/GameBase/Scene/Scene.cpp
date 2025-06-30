#include"pch.h"
#include"Scene.h"
#include"GameBase/Actor.h"
#include "GameBase/Managers.h"
#include "GameBase/Camera/Camera.h"


/// <summary>
/// コンストラクタ
/// </summary>
Scene::Scene()
	:
	m_actors{}
	,m_holdActors{}
	,m_updateNow{false}
	,m_isChangeScene{}
	,m_isActorDestroy{false}
{

	m_renderMangaer = std::make_unique<RenderManager>();

	m_collisionManager = std::make_unique<CollisionManager>();

	m_rigidbodyManager = std::make_unique<RigidbodyManager> ();

	m_uiManager = std::make_unique<UIManager>();


}

/// <summary>
/// デストラクタ
/// </summary>
Scene::~Scene()
{
	for (auto& actor : m_actors)
	{
		actor->Finalize();
	}

	m_actors.clear();

	m_holdActors.clear();

}

/// <summary>
/// 初期化処理
/// </summary>
void Scene::Initialize()
{
	for (auto& actor : m_actors)
	{
		actor->Initialize();
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Scene::Update(float deltaTime)
{
	



	//更新フラグをtrueに変更
	m_updateNow = true;
	// アクターの更新をする
	for (auto& actor : m_actors)
	{
		if (!actor->GetActive()) { continue; }
		actor->Update(deltaTime);
	}

	SceneUpdate(deltaTime);


	// シーン別の更新
	m_updateNow = false;

	m_rigidbodyManager->Update(deltaTime);

	m_collisionManager->Update(deltaTime);

	GetCamera()->Update(deltaTime);

	m_uiManager->Update(deltaTime);

	// 保留オブジェクトを更新オブジェクトに
	std::move(m_holdActors.begin(), m_holdActors.end(), std::back_inserter(m_actors));
	m_holdActors.clear();
	// アクターの削除
	RemoveActor();

}

/// <summary>
/// 描画処理
/// </summary>
void Scene::Render()
{
	
	m_renderMangaer->Render(*GetCamera());
	
	// シーンの描画
	SceneRender();

}

/// <summary>
/// アクターの削除
/// </summary>
void Scene::RemoveActor()
{
	// 削除要請がないなら返す
	if (!m_isActorDestroy) { return; }
	// 削除要素を削除
	m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [&](
		std::unique_ptr<Actor>& actor) {
			return actor->GetIsDestroy();
		}), m_actors.end());
	// 削除要請フラグをオフに
	m_isActorDestroy = false;
}