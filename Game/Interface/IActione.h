/*
	IBehaviorNode.h
	渡邊翔也
	行動のインタフェース
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IBehaviorNode.h"



class IAction
{
public:
	//アクションの状態
	enum class ActionState
	{
		NONE,
		RUNNING,
		END
	};

public:
	//デストラクタ
	virtual ~IAction() = default;
	//初期化
	//virtual void Initialize() = 0;
	//更新処理
	virtual ActionState Update(const float& elapsedTime) = 0;
	//状態に入った時
	virtual void Enter() = 0;
	//状態を抜けた時
	virtual void Exit() = 0;

};
