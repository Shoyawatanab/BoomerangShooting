/*
	クラス名    : PickableComponent
	説明        : 拾われる側コンポーネント
	補足・注意点:
*/
#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"
#include "Game/Manager/PickUp/PickUpManager.h"

class PickableComponent : public Component
{
public:

	//回収可能かの取得　ture:可能  false:不可能 
	bool GetIsPossible() { return m_isPossible; }
	//回収可能かのセット　ture:可能  false:不可能 
	void SetIsPossible(const bool& isPossible) {  m_isPossible = isPossible; }

	//回収時の実行関数のセット
	void SetOnPickUpFunction(std::function<void()> function) { m_onPickUp = function; };
	//回収可能時の実行関数のセット
	void SetRecoverableFunction(std::function<void()> functoin) { m_recoverable = functoin; }
	//回収不可能時の実行関数のセット
	void SetUnrecoverableFunction(std::function<void()> function) { m_unrecoverable = function; }


public:
	//コンストラク
	PickableComponent (Actor* owner, PickUpManager::PickUpType type);
	//デストラクタ
	~PickableComponent () override;


	//回収時
	void OnPickUp();
	//回収できるようになった
	void OnRecoverable();
	//回収できなくなったとき
	void OnUnrecoverable();


private:

	//回収可能か　ture:可能  false:不可能 
	bool m_isPossible;

	//回収時の実行関数
	std::function<void()> m_onPickUp;
	//回収可能時の実行関数
	std::function<void()> m_recoverable;
	//回収不可能時の実行関数
	std::function<void()> m_unrecoverable;
};