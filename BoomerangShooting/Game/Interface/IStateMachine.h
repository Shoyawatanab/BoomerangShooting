/*
* ステーとパターンのインターフェース
*/
#pragma once
#include "pch.h"

class IState;
class CommonResources;


template<typename T>
class IStateMachine
{
public:
	//デストラクタ
	virtual ~IStateMachine() = default;
	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	//状態の変更
	virtual void ChangeState(T* nextState) = 0;

};
