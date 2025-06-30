#pragma once
#include "GameBase/Interface/IState.h"

class BoomerangStateMachine;
class Boomerang;
class Player;

class BoomerangIdle : public IState
{

public:
	//コンストラクタ
	BoomerangIdle(BoomerangStateMachine* stateMahine,Boomerang* boomerang, Player* player);
	//デストラクタ
	~BoomerangIdle() override;

	// 更新する
	void Update(const float& deltaTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:
	//ブーメラン
	Boomerang* m_boomerang;
	//ステートマシーン
	BoomerangStateMachine* m_stateMahine;
	//
	Player* m_player;
};

