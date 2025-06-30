#include "pch.h"
#include "ActionController.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="actions">実行順配列</param>
ActionController::ActionController()
	:
	m_actionList{}
	,m_currentIndex{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
ActionController::~ActionController()
{
	m_actionList.clear();
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
IAction::ActionState ActionController::Update(const float& elapsedTime)
{
	//状態の更新
	if(m_actionList[m_currentIndex]->Update(elapsedTime) == IAction::ActionState::END)
	{
		//状態が終わったら
		ChangeState();
		//すべての状態が終わった
		if (m_currentIndex >= m_actionList.size())
		{
			m_currentIndex = 0;
			return IAction::ActionState::END;

		}

	}


	return IAction::ActionState::RUNNING;

}

/// <summary>
/// 状態に入った時
/// </summary>
void ActionController::Enter()
{

	m_currentIndex = 0;


	if (!m_actionList.empty())
	{
		m_actionList[m_currentIndex]->Enter();
	}


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void ActionController::Exit()
{
	m_currentIndex = 0;
}

/// <summary>
/// 状態の切り替え
/// </summary>
void ActionController::ChangeState()
{
	//初期化段階では行わないように
	if (m_currentIndex != 0)
	{
		//状態を抜けた時の処理
		m_actionList[m_currentIndex]->Exit();
	}

	m_currentIndex++;

	//最後のStateが終わったら
	if (m_currentIndex >= m_actionList.size())
	{
		return;
	}
	//状態に入った時の処理
	m_actionList[m_currentIndex]->Enter();
}

/// <summary>
/// アクションの追加
/// </summary>
/// <param name="actions">アクション配列</param>
void ActionController::AddAction(std::vector<IAction*> actions)
{

	m_actionList = std::move(actions);

}

