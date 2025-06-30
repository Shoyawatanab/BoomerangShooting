#pragma once
#include "Game/Observer/Telegram.h"


// IObserverインターフェースを定義する
class IBaseObserver
{
public:
	//通知時に呼び出される
	virtual ~IBaseObserver() = default;

};

