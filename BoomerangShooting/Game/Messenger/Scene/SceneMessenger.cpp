#include "pch.h"
#include "SceneMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneMessenger::SceneMessenger()
	:
	m_list{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
SceneMessenger::~SceneMessenger()
{
	m_list.clear();
}

/// <summary>
/// リストに追加
/// </summary>
/// <param name="types">登録するタイプ配列</param>
/// <param name="observer">オブザーバー</param>
void SceneMessenger::Rigister(std::vector<SceneMessageType> types, IObserver<SceneMessageType>* observer)
{
	//タイプだけ回す
	for (auto& type : types)
	{
		//追加
		m_list[type].push_back(observer);

	}
}


/// <summary>
/// 通知する
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void SceneMessenger::Notify(SceneMessageType type, void* datas)
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
		obsever->Notify(type, datas);
	}


}

/// <summary>
/// クリア
/// </summary>
void SceneMessenger::Clear()
{
	m_list.clear();
}









