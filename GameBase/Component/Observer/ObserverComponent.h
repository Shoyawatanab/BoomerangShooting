/*
	クラス名    : ObserverComponent
	説明        : 通知を受け取るコンポーネント
	補足・注意点:
*/

#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"
#include "GameBase/Messenger/Messenger.h"
#include "GameBase/Messenger/IObserver.h"


//通知の種類
template<typename MessageType>
class ObserverComponent : public Component , public IObserver<MessageType>
{
public:
	//コンストラク
	ObserverComponent(Actor* owner)
		:
		Component(owner)
	{

	};

	//デストラクタ
	~ObserverComponent() override
	{
		//削除
		m_messenger->Delete(this);
	};
	
	/// <summary>
	/// 登録
	/// </summary>
	/// <param name="types">通知の種類</param>
	/// <param name="function">呼び出し関数</param>
	void Rigister(std::vector<MessageType> types, std::function<void(MessageType, void*)> function)
	{
		//メッセンジャーの取得
		m_messenger = Messenger<MessageType>::GetInstance();
		//メッセンジャーに登録
		m_messenger->Rigister(types, this);
		//呼び出し関数のセット
		m_notifyFunction = function;

	};


	/// <summary>
	/// 関数実行
	/// </summary>
	/// <param name="type">通知の種類</param>
	/// <param name="datas">追加データ</param>
	void FunctionExecution(MessageType type, void* datas) override
	{
		//関数の実行
		m_notifyFunction(type, datas);
	}

private:

	//呼び出し関数
	std::function<void(MessageType , void*)> m_notifyFunction;

	//マネージャー
	Messenger<MessageType>* m_messenger;

};