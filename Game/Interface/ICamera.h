/*
* カメラのStateのインターフェース
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IState.h"


class ICamera : public IState
{
public:
	//デストラクタ
	virtual ~ICamera() = default;
	//Matrixの取得
	virtual const DirectX::SimpleMath::Matrix& GetViewMatrix() = 0;

};
