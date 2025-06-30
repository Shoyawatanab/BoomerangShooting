/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Player;


enum class PlayerState
{
	IDEL                                  //通常
	, BOOMERANG_ATTACK					  //ブーメラン攻撃
	, BOOMERANG_GET_READY				  //ブーメラン構え
};

class PlayerStateMachine : public StateMachine<IState,PlayerState>, public IObserver<SceneMessageType>
{

public:
	//コンストラクタ
	PlayerStateMachine(Player* player);
	//デストラクタ
	~PlayerStateMachine() override;


	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) override;

	
};