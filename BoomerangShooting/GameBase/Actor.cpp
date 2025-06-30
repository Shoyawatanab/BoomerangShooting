#include"pch.h"
#include"Actor.h"

#include"Component/Transform/Transform.h"
#include "GameBase/Scene/Scene.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene"></param>
Actor::Actor(Scene* scene)
	:
	m_scene{scene},
	m_components{},
	m_transform{nullptr},
	m_isActive{true},
	m_isDestroy{false},
	m_isComponentDestroy{false}
{
	m_transform = AddComponent<Transform>(this);
}

/// <summary>
/// デストラクタ
/// </summary>
Actor::~Actor()
{
	m_components.clear();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Actor::Update(const float& deltaTime)
{
	if (!m_isActive) { return; }

	// コンポーネント更新処理
	UpdateComponent(deltaTime);
	// コンポーネント個別アップデート
	UpdateActor(deltaTime);
	// コンポーネント削除
	RemoveComponent();
}

/// <summary>
/// コンポーネント更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Actor::UpdateComponent(const float& deltaTime)
{
	// コンポーネントを回す
	for (auto& component : m_components)
	{
		// コンポーネントアクティブ
		if (!component->GetActive()) { continue; }
		component->Update(deltaTime);
	}
}



/// <summary>
/// 削除
/// </summary>
void Actor::Destroy()
{

	// アクターの破壊処理をオンにする
	GetScene()->ActorDestroyOn();

}

/// <summary>
/// 破壊するコンポーネントを検索して、削除
/// </summary>
void Actor::RemoveComponent()
{
	// 破壊申請がないなら返す
	if (m_isComponentDestroy) { return; }
	// 削除要素を排除する
	m_components.erase(std::remove_if(m_components.begin(), m_components.end(),
		[&](std::unique_ptr<Component>& comp)
		{
			// 対応コンポーネントの破壊処理を呼ぶ
			return comp->GetIsDestroy();
		}), m_components.end());
	// 破壊要請をオフにする
	m_isComponentDestroy = true;
}

/// <summary>
/// アクティブフラグ変更
/// </summary>
/// <param name="active"></param>
void Actor::SetActive(bool active)
{
	// アクティブ状態の代入
	m_isActive = active;
	// 子へ伝播させる
	for (auto& children : m_transform->GetAllChild())
	{
		children->GetActor()->SetActive(active);
	}
	// コンポーネント
	for (auto& component : m_components)
	{
		component.get()->SetActive(active);
	}

	//結果に応じた関数を呼ぶ
	if (active)
	{
		OnEnable();
	}
	else
	{
		OnDisable();
	}

}