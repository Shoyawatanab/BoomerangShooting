#include "pch.h"
#include "PlayerStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Player//State/PlayerStates.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerStateMachine::PlayerStateMachine(Player* player)
{
	//Messenger::GetInstance()->Rigister<PlayerMessageType>(player->GetID(), this);
	
	//IDEL状態の追加
	AddState(PlayerState::IDEL,std::make_unique<PlayerIdle>(this, player));
	//BOOMERANG_ATTACK状態の追加
	AddState(PlayerState::BOOMERANG_ATTACK, std::make_unique<PlayerBoomerangAttack>(this, player));
	//BOOMERANG_GETREADY状態
	AddState(PlayerState::BOOMERANG_GET_READY, std::make_unique<PlayerBoomerangGetReady>(this, player));

	SetStartState(PlayerState::IDEL);

	//メッセージの登録
	SceneMessenger::GetInstance()->Rigister(
		{
		 SceneMessageType::PLAYER_IDLE_STATE
		,SceneMessageType::PLAYER_BOOMERANG_ATTACK_STATE
		,SceneMessageType::PLAYER_BOOMERANG_GET_READY_STATE
		}
		, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerStateMachine::~PlayerStateMachine()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void PlayerStateMachine::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{
		case SceneMessageType::PLAYER_IDLE_STATE:
			ChangeState(PlayerState::IDEL);
			break;
		case SceneMessageType::PLAYER_BOOMERANG_GET_READY_STATE:
			ChangeState(PlayerState::BOOMERANG_GET_READY);
			break;
		case SceneMessageType::PLAYER_BOOMERANG_ATTACK_STATE:
			ChangeState(PlayerState::BOOMERANG_ATTACK);
			break;
		default:
			break;
	}

}


