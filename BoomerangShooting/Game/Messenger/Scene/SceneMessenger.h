#pragma once
#include "Libraries/WataLib/Singleton.h"
#include "GameBase/Messenger/IObserver.h"
#include "SceneMessageType.h"
#include <unordered_map>



class SceneMessenger : public Singleton<SceneMessenger>
{
	friend class Singleton<SceneMessenger>;

public:
	//コンストラクタ
	SceneMessenger();
	//デストラクタ
	~SceneMessenger() override;
	//リストに登録
	void Rigister(std::vector<SceneMessageType> types,IObserver<SceneMessageType>* observer);
	//通知
	void Notify(SceneMessageType type, void* = nullptr);
	//クリア
	void Clear();

private:

	std::unordered_map<SceneMessageType, std::vector<IObserver<SceneMessageType>*>> m_list;

};




