#pragma once
#include "Game/Interface/IActione.h"

class BossEnemy;


class BossDeathEndAction : public IAction
{
public:

	//時間　アニメーションにあわせる
	static constexpr float DEATH_TIME = 3.0f;

public:
	//コンストラクタ
	BossDeathEndAction(BossEnemy* bossEnemy);
	//デストラクタ
	~BossDeathEndAction() override;
	//更新処理
	ActionState Update(const float& elapsedTime)  override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:

	//所有者
	BossEnemy* m_bossEnemy;

};
#pragma once
