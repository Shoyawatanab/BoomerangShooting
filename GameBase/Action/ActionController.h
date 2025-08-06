/*
	クラス名     : ActionController
	説明         : アクションのコントローラーの基底クラス　今回はボス敵で使用
	補足・注意点 :
*/
#pragma once
#include "Game/Interface/IActione.h"


class ActionController 
{
public:
	//コンストラク
	ActionController();
	//デストラクタ
	virtual ~ActionController() = 0;
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

	//行動の中止
	virtual void ActionCancel() {};

private:
	//各状態の保存変数
	std::vector<IAction*> m_actionList;
	//添え字
	int m_currentIndex;

};


