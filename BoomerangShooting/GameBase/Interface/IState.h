/*
* ステーとパターンのインターフェース
*/
#pragma once
#include "pch.h"

class CommonResources;


class IState
{
public:
	//デストラクタ
	virtual ~IState() = default;
	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	//状態に入った時
	virtual void Enter() = 0;
	//状態を抜けた時
	virtual void Exit() = 0;



};
