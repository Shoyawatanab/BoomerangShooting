/*
	IBehaviorNode.h
	渡邊翔也
	ビヘイビアツリーの実行のみのノード
	子を持たない
*/
#pragma once
#include "pch.h"



class IBehaviorNode
{
public:

	//実行状態
	enum class State
	{
		SUCCESS,         //成功
		FAILURE,      //失敗
	};

public:
	//デストラクタ
	virtual ~IBehaviorNode() = default;
	//初期化
	virtual void Initialize() = 0;
	//更新処理
	virtual State Update(const float& deltaTime) = 0;

	virtual void Finalize() = 0;
};
