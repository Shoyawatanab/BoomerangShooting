#include"pch.h"
#include"Actor.h"
#include"Component.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="actor">所属アクター</param>
/// <param name="updateOrder">アップデート遅延用</param>
Component::Component(Actor* actor, int updateOrder)
	:
	m_actor{actor},
	m_isActive{true},
	m_updateOrder{updateOrder},
	m_isDestroy{false}
{

}

/// <summary>
/// デストラクタ
/// </summary>
Component::~Component()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Component::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/// <summary>
/// 破壊する
/// </summary>
void Component::Destroy()
{
	// アクターの破壊処理をオンにする
	GetActor()->ComponentDestroyOn();
	// 死亡フラグ設定
	m_isDestroy = true;
	// アクティブフラグ設定
	SetActive(false);
}


