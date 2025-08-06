/*
	クラス名     : BossDeathActionController
	説明         : ボス敵の倒したときのコントローラー
	補足・注意点 :
*/
#pragma once
#include "GameBase/Action/ActionController.h"

class BossDeathAction;
class BossDeathEndAction;

class BossEnemy;


class BossDeathActionController : public ActionController
{
public:
	//コンストラク
	BossDeathActionController(BossEnemy* bossEnemy);
	//デストラクタ
	~BossDeathActionController()override;

private:
	//通常
	std::unique_ptr<BossDeathAction> m_idle;
	//終了
	std::unique_ptr<BossDeathEndAction> m_end;
};
