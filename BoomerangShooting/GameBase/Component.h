#pragma once
class Scene;
class Actor;

class Component
{
public:
	// アクターの取得
	Actor* GetActor() const { return m_actor; }
	// アクティブフラグ
	void SetActive(bool isActive) { m_isActive = isActive; }
	bool GetActive() const { return m_isActive; }
	// オーダー取得
	int GetUpdateOrder() const { return m_updateOrder; }
	// 破壊フラグ取得
	bool GetIsDestroy() const { return m_isDestroy; }
public:
	// コンストラクタ
	Component(Actor* owner, int updateOrder = 0);
	// デストラクタ
	virtual ~Component();
	// アップデート
	virtual void Update(const float& deltaTime);
	// 削除
	void Destroy();

private:
	// 所属アクター
	Actor* m_actor;
	// アクティブフラグ
	bool m_isActive;
	// 破壊フラグ
	bool m_isDestroy;
	// 更新オーダー
	int m_updateOrder;
};