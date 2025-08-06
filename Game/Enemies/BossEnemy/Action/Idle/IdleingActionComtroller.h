/*
	クラス名     : IdleingAction
	説明         : ボス敵の通常のコントローラー
	補足・注意点 :
*/
#pragma once
#include "GameBase/Action/ActionController.h"

class IdleingAction;


class IdleingActionComtroller : public ActionController
{
public:
	//コンストラク
	IdleingActionComtroller();
	//デストラクタ
	~IdleingActionComtroller()override;

private:
	//通常
	std::unique_ptr<IdleingAction> m_idle;

};
