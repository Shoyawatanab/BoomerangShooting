#pragma once
#include "GameBase/Actor.h"



class WeaponBase : public Actor
{
public:

	//状態
	enum class WeaponState
	{
		BOOMERANG_IDLE                                 //ブーメラン通常状態
		,BOOMERANG_GET_READY						   //ブーメラン構え状態
		,BOOMERANG_THROW							   //ブーメラン投げ状態
	};

public:

	
	//状態の取得
	WeaponState GetWeaponState() { return m_state; }
	//状態のセット
	void SetWeaponState(WeaponState state) { m_state = state; }

public:
	//コンストラクタ
	WeaponBase(Scene* scene);
	//デストラクタ
	~WeaponBase() override;

	//ステートの変更  Factoryからの状態変化の通知用
	void ChangeState(WeaponState nextState);
	//個別のステート変更
	virtual void ActorChangeState(WeaponState nextState) = 0;

private:
	//状態
	WeaponState m_state;

};

