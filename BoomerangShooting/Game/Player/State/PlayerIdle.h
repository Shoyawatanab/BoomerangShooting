/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "GameBase/Interface/IState.h"

class PlayerStateMachine;
class Player;
class CommonResources;

class PlayerIdle : public IState 
{
public:
	//コンストラクタ
	PlayerIdle(PlayerStateMachine* stateMachine,Player* player) ;
	//デストラクタ
	~PlayerIdle() override;

	// 更新する
	void Update(const float& deltaTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


private:
	//プレイヤ
	Player* m_player;

	PlayerStateMachine* m_stateMahine;
	
};