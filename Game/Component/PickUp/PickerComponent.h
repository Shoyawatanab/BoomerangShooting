/*
	クラス名    : PickerComponent
	説明        : 拾う側コンポーネント
	補足・注意点:　このゲームオリジナルコンポーネント
	　　　　　　　プレイシーンにマネージャーがある
*/
#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"
#include "Game/Manager/PickUp/PickUpManager.h"

class PickUpManager;

class PickerComponent : public Component
{
public:

	//初期回収範囲範囲
	static constexpr float INITIAL_RADIUS = 1.0f;

public:

	//回収範囲の取得
	float GetPickUpRadius() const { return m_pickUpRadius; }
	//回収可能かの取得　true:回収可能 false :回収不可能
	float GetIsPickUp() const { return m_isPickUp; }
	//回収可能かのセット　true:回収可能 false :回収不可能
	void SetIsPickUp(bool isPickUp) { m_isPickUp = isPickUp; }
	//回収可能状態の取得　true: 回収可能状態　false:回収不可能状態
	bool GetIsRecoverable() { return m_isRecoverable; }
	//回収可能状態のセット　true: 回収可能状態　false:回収不可能状態
	void SetIsRecoverable(bool recoverable) { m_isRecoverable = recoverable; }
	//回収時の実行関数のセット
	void SetOnPickUpFunction(std::function<void()> function) { m_onPickUp = function; };
	//回収可能時の実行関数のセット
	void SetRecoverableFunction(std::function<void()> functoin) { m_recoverable = functoin; }
	//回収不可能時の実行関数のセット
	void SetUnrecoverableFunction(std::function<void()> function) { m_unrecoverable = function; }

	//回収タイプの取得
	PickUpManager::PickUpType GetPickUpType() { return m_type; }

public:
	//コンストラク
	PickerComponent(Actor* owner,PickUpManager::PickUpType type,float pickUpRadius = INITIAL_RADIUS);
	//デストラクタ
	~PickerComponent() override;

	//回収の実行
	void TryPickUp();

	//回収時
	void OnPickUp();
	//回収できるようになった
	void OnRecoverable();
	//回収できなくなったとき
	void OnUnrecoverable();

private:

	//回収範囲
	float m_pickUpRadius;

	//回収可能か　true:回収可能 false :回収不可能
	bool m_isPickUp;
	
	//回収可能状態か true: 回収可能状態　false:回収不可能状態    回収時の判定で使用
	bool m_isRecoverable;
	//回収時の実行関数
	std::function<void()> m_onPickUp;
	//回収可能時の実行関数
	std::function<void()> m_recoverable;
	//回収不可能時の実行関数
	std::function<void()> m_unrecoverable;

	//マネージャー
	PickUpManager* m_manger;
	//タイプ
	PickUpManager::PickUpType m_type;

};