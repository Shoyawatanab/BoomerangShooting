/*
	クラス名     : PlayerStateMachine
	説明         : プレイヤのブーメランのステートマシーン
	補足・注意点 :
*/
#include "pch.h"
#include "PlayerStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Player//State/PlayerStates.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"

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


	//通知を受け取るコンポーネントの追加
	auto ob = player->AddComponent<ObserverComponent<SceneMessageType>>(player);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			 SceneMessageType::PLAYER_IDLE_STATE
			,SceneMessageType::PLAYER_BOOMERANG_ATTACK_STATE
			,SceneMessageType::PLAYER_BOOMERANG_GET_READY_STATE
		}
		, std::bind(&PlayerStateMachine::Notify, this, std::placeholders::_1, std::placeholders::_2)
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

	UNREFERENCED_PARAMETER(datas);

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


