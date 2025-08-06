/*
	クラス名     : BoomerangStateMachine
	説明         : ブーメランのステートマシーン
	補足・注意点 :
*/
#pragma once
#include "GameBase/StateMachine/StateMachine.h"

class Boomerang;
class Player;

enum class BoomerangState
{
	IDEL                //通常
	,THROW				//投げられている
	,GET_READY			//構えている
	,BOUNCE				//跳ね返り
	,DORP               //落ちた
};

class BoomerangStateMachine : public StateMachine<IState, BoomerangState>
{

public:
	//コンストラクタ
	BoomerangStateMachine(Boomerang* boomrang, Player* player);
	//デストラクタ
	~BoomerangStateMachine() override;

	//派生先のChangeState時の処理
	void DerivationChangeState(BoomerangState state);

private:

	Boomerang* m_boomerang;

};
