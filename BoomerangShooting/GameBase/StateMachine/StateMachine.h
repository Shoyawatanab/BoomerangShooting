#pragma once

#include "GameBase/Interface/IState.h"
#include <unordered_map>

//ステートクラスとステートの列挙型の種類
template<typename StateType,typename StateEnumType>
class StateMachine
{

public:

	//現在の状態の取得
	StateEnumType GetCurrentState() { return m_currentState.first; }

public:

	//コンストラクタ
	StateMachine()
		:
		m_currentState{}
		,m_stateList{}
	{
	};

	//デストラクタ
	virtual ~StateMachine() {};

	/// <summary>
	/// ステートの追加
	/// </summary>
	/// <param name="enumType">ステートの種類</param>
	/// <param name="state">ステートクラス</param>
	void AddState(StateEnumType enumType,std::unique_ptr<StateType> state)
	{
		//すでに登録済みなら
		if (GetIsRegister(enumType))
		{
			return;
		}
		//追加
		m_stateList.insert({ enumType,std::move(state) });

	}

	// 更新処理
	void Update(const float& deltaTime)
	{

		m_currentState.second->Update(deltaTime);
		
	};

	/// <summary>
	/// ステートの変更
	/// </summary>
	/// <param name="enumType">ステートの種類</param>
	void ChangeState(StateEnumType enumType)
	{
		//ステートがなければ
		if (m_currentState.second == nullptr)
		{
			return;
		}
		//ステートの終了処理
		m_currentState.second->Exit();
		//実行ステートの情報の変更
		m_currentState.first = enumType;
		m_currentState.second = m_stateList[enumType].get();
		//ステートの開始処理
		m_currentState.second->Enter();

		DerivationChangeState(enumType);

	}

	//初期ステートのセット
	void SetStartState(StateEnumType enumTye)
	{
		//ステートがなければ
		if (!GetIsRegister(enumTye))
		{
			return;
		}

		//初期ステートのセット
		m_currentState.first = enumTye;
		m_currentState.second = m_stateList[enumTye].get();
		////ステートの開始処理
		m_currentState.second->Enter();

	}

	//派生先のChangeState時の処理
	virtual void DerivationChangeState(StateEnumType enumType) {};

private:

	/// <summary>
	/// 登録されているか
	/// </summary>
	/// <param name="enumType">ステートの種類</param>
	/// <returns>true : されている false : されていない</returns>
	bool GetIsRegister(StateEnumType enumType)
	{
		//探す
		auto it = m_stateList.find(enumType);
		//あれば
		if (it != m_stateList.end())
		{
			//ある
			return true;
		}
		//ない
		return false;
	}



private:

	//実行中ステート
	std::pair<StateEnumType, StateType*> m_currentState;
	//ステートの保存リスト
	std::unordered_map<StateEnumType, std::unique_ptr<StateType>> m_stateList;




};