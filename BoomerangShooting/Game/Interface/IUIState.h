/*
* ステーとパターンのインターフェース
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IState.h"



class IUIState : public IState
{
public:

	//描画
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;


};
