/*
	クラス名     : PlayerBoomerangAttack
	説明         : プレイヤのブーメラン攻撃状態
	補足・注意点 :
*/
#pragma once
#include "GameBase/Interface/IState.h"

class PlayerStateMachine;
class Player;

class PlayerBoomerangAttack : public IState 
{
public:

	enum class ThrowState
	{
		RIGHT = 0
		,FRONT
		, LEFT

	};

	enum class ThrowQuantityState
	{
		ONE,     //１つなげる
		THREE	 //３つなげる
	};



public:
	//コンストラクタ
	PlayerBoomerangAttack(PlayerStateMachine* stateMachine, Player* player) ;
	//デストラクタ
	~PlayerBoomerangAttack() override;


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


	//投げの状態
	ThrowState m_throwState;
	//投げる個数の状態
	ThrowQuantityState m_throwQuantityState;


};