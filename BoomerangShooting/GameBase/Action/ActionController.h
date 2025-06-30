/*
* プレイヤクラス　
*/

#pragma once
#include "Game/Interface/IActione.h"


class ActionController 
{
public:
	//コンストラク
	ActionController();
	//デストラクタ
	virtual ~ActionController();
	//更新処理
	IAction::ActionState Update(const float& elapsedTime);
	//状態に入った時
	virtual void Enter();
	//状態を抜けた時
	virtual void Exit();
	//状態の切り替え
	void ChangeState();
	//行動の追加
	void AddAction(std::vector<IAction*> actions);

private:
	//各状態の保存変数
	std::vector<IAction*> m_actionList;
	//添え字
	int m_currentIndex;

};


