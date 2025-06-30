#include "pch.h"
#include "ActionManager.h"
#include "ActionController.h"

/// <summary>
/// コンストラクタ
/// </summary>
ActionManager::ActionManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ActionManager::~ActionManager()
{
	//m_action.first.clear();
	//m_actionList.clear();
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
/// <returns>true: 実行終了  false:　実行中</returns>
bool ActionManager::Update(const float& deltaTime)
{
	if(	m_action.second->Update(deltaTime) == IAction::ActionState::END)
	{
		return true;
	}

	return false;
}

void ActionManager::SetStartAction(const std::string& actionName)
{
	m_action.first = actionName;
	m_action.second = m_actionList[actionName].get();
}

/// <summary>
/// アクションの変更
/// </summary>
/// <param name="actionName">アクション名</param>
void ActionManager::ChangeAction(const std::string& actionName)
{
	//リストから佐賀図
	auto it = m_actionList.find(actionName);

	//あれば
	if (it != m_actionList.end())
	{
		//切り替え前の行動があるかどうか
		if (m_action.second != nullptr)
		{
			//状態を抜けるときの処理
			m_action.second->Exit();
		}
		//実行行動の名前の切り替え
		m_action.first = actionName;
		//実行行動の切り替え
		m_action.second = it->second.get();
		//状態に入った時の処理
		m_action.second->Enter();


	}

}

/// <summary>
/// アクションの追加
/// </summary>
/// <param name="">アクション名</param>
/// <param name=""></param>
void ActionManager::AddAction(const std::string& name, std::unique_ptr<ActionController>action)
{

	m_actionList[name] = std::move(action);

}
