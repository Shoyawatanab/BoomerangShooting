/*
ゲーム全体のメッセンジャークラス

*/
#pragma once
#include "Libraries/WataLib/Singleton.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Global/GlobalMeesageType.h"
#include <unordered_map>


class GlobalMessenger : public Singleton<GlobalMessenger>
{
	friend class Singleton<GlobalMessenger>;
public:

	//コンストラク
	GlobalMessenger();
	//デストラクタ
	~GlobalMessenger() override;

	//リストに登録
	void Rigister(std::vector<GlobalMessageType> types, IObserver<GlobalMessageType>* observer);
	//通知
	void Notify(GlobalMessageType type, void* datas = nullptr);
	//クリア
	void Clear();

private:

	std::unordered_map<GlobalMessageType, std::vector<IObserver<GlobalMessageType>*>> m_list;


};