/*
	クラス名     : PlayerStateMachine
	説明         : プレイヤのブーメランのステートマシーン
	補足・注意点 :
*/
#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "Game/Messenger/Messengers.h"

class Player;


enum class PlayerState
{
	IDEL                                  //通常
	, BOOMERANG_ATTACK					  //ブーメラン攻撃
	, BOOMERANG_GET_READY				  //ブーメラン構え
};

class PlayerStateMachine : public StateMachine<IState,PlayerState>
{

public:
	//コンストラクタ
	PlayerStateMachine(Player* player);
	//デストラクタ
	~PlayerStateMachine() override;


	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);

	
};