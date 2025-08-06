/*
	クラス名     : Messenger
	説明         : メッセージを送るクラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/WataLib/Singleton.h"
#include <unordered_map>
#include "GameBase/Messenger/IObserver.h"

template<typename MessageType>
class IObserver;


template<typename MessageType>
class Messenger : public Singleton<Messenger<MessageType>>
{
	friend class Singleton<Messenger<MessageType>>;

public:
	//コンストラクタ
	Messenger()
		:
		m_list{}
	{

	};

	//デストラクタ
	~Messenger() override
	{
		//クリア
		m_list.clear();
	};

	//リストに登録
	void Rigister(std::vector<MessageType> types, IObserver<MessageType>* observer)
	{
		//タイプだけ回す
		for (auto& type : types)
		{
			//追加
			m_list[type].push_back(observer);

		}
	};
	
	//リストから削除
	void Delete(IObserver<MessageType>* observer)
	{
		//Typeだけ回す
		for (auto& type : m_list)
		{
			//Typeごとにオブザーバーがあるか探す
			auto it = std::find(type.second.begin(), type.second.end(), observer);

			//存在すれば
			if (it != type.second.end())
			{
				//削除
				type.second.erase(it);
			}
		}

	};

	//通知
	void Notify(MessageType type, void* datas = nullptr)
	{

		//探す
		auto it = m_list.find(type);
		//なければ
		if (it == m_list.end())
		{
			return;
		}

		//オブザーバーに通知
		for (auto& obsever : it->second)
		{
			obsever->FunctionExecution(type, datas);
		}

	};
	
	//クリア
	void Clear()
	{
		m_list.clear();

	};

private:

	//リスト
	std::unordered_map<MessageType, std::vector<IObserver<MessageType>*>> m_list;

};




