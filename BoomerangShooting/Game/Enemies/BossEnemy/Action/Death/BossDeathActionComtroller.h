/*
	@file	BossDeathActionComtroller.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Action/ActionController.h"

class BossDeathAction;
class BossDeathEndAction;

class BossEnemy;


class BossDeathActionComtroller : public ActionController
{
public:
	//コンストラク
	BossDeathActionComtroller(BossEnemy* bossEnemy);
	//デストラクタ
	~BossDeathActionComtroller()override;

private:
	//通常
	std::unique_ptr<BossDeathAction> m_idle;
	//終了
	std::unique_ptr<BossDeathEndAction> m_end;
};
