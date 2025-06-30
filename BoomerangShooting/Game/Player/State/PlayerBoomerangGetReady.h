#pragma once
#include "GameBase/Interface/IState.h"


class PlayerStateMachine;
class Player;

class PlayerBoomerangGetReady : public IState
{
public:
	//コンストラクタ
	PlayerBoomerangGetReady(PlayerStateMachine* stateMachine, Player* player);
	//デストラクタ
	~PlayerBoomerangGetReady() override;

	// 更新する
	void Update(const float& deltaTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;
private:

	//プレイヤ
	Player* m_player;
	//ステートマシーン
	PlayerStateMachine* m_stateMahine;


};
