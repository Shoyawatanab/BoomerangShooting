#pragma once


#include "Game/Observer/EventParams.h"

// IObserverインターフェースを定義する
class IKeyBoardObserver
{
public:
	// キーが押下げられたら時に呼び出される
	virtual void OnKeyPressed(const DirectX::Keyboard::Keys& key) = 0;

};
