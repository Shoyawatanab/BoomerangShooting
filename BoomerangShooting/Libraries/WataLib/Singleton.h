/*
* プレイヤクラス　
*/

#pragma once


template<typename T>
class Singleton
{
public:

	static T* GetInstance()
	{
		if (instance == nullptr)
		{
			instance.reset(new T());
		}
		return instance.get();
	}

public:
	
	//コピー禁止
	Singleton(const T&) = delete;
	Singleton& operator=(const T&) = delete;
	//ムーブ禁止
	Singleton(T&&) = delete;
	Singleton& operator=(T&&) = delete;

protected:
	
	Singleton() = default;

	virtual ~Singleton() = default;

private:

	//インスタンス
	static std::unique_ptr<T> instance;

};


template<typename T> 
std::unique_ptr<T> Singleton<T>::instance = nullptr;
