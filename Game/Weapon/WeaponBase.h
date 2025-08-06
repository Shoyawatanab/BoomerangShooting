/*
	クラス名     : WeaponBase
	説明         : 武器のベースクラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"


template<typename T>
class WeaponBase : public Actor
{
public:

	////状態
	//enum class WeaponState
	//{
	//	BOOMERANG_IDLE                                 //ブーメラン通常状態
	//	,BOOMERANG_GET_READY						   //ブーメラン構え状態
	//	,BOOMERANG_THROW							   //ブーメラン投げ状態
	//	,BOOMERANG_BOUNCE							   //ブーメラン跳ね返り状態
	//};

public:

	//状態の取得
	T GetState() { return m_state; }
	//状態のセット
	void SetState(T state) { m_state = state; }

public:
	//コンストラクタ
	WeaponBase(Scene* scene)
		:
		Actor(scene)
		,m_state{}
	{
	};

	//デストラクタ
	~WeaponBase() override
	{
	};

	//ステートの変更  Factoryからの状態変化の通知用
	void ChangeState(T nextState) 
	{
		//個別のステート変更
		ActorChangeState(nextState);

		//状態の変更
		m_state = nextState;
	};

	//個別のステート変更
	virtual void ActorChangeState(T nextState) = 0;

private:
	//状態
	T m_state;

};

