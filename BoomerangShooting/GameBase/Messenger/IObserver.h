#pragma once


// IObserverインターフェースを定義する
template <typename T>
class IObserver 
{
public:
	//通知時に呼び出される
	virtual void Notify(T type,void* datas) = 0;

};

