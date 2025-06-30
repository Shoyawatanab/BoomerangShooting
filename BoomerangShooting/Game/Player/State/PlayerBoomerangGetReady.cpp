#include "pch.h"
#include "PlayerBoomerangAttack.h"
#include "PlayerBoomerangGetReady.h"
#include "GameBase/Common/Commons.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stateMachine">ステートマシーン</param>
/// <param name="player">プレイヤ</param>
PlayerBoomerangGetReady::PlayerBoomerangGetReady(PlayerStateMachine* stateMachine, Player* player)
	:
	m_player{player}
	,m_stateMahine{stateMachine}
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBoomerangGetReady::~PlayerBoomerangGetReady()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlayerBoomerangGetReady::Update(const float& deltaTime)
{
	using namespace DirectX;


	const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();

	//投げ方の変更

	//投げるのをやめる
	if (tracker->rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		//プレイヤの状態をIDELに
		SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_IDLE_STATE);
		//プレイヤの構え終了の通知
		SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_GET_REDAY_END);
		//ブーメランの状態を通常に
		SceneMessenger::GetInstance()->Notify(SceneMessageType::BOOMERANG_IDEL_STATE);

	}
	//投げる
	else if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		//ブーメランの状態をTHROWに
		SceneMessenger::GetInstance()->Notify(SceneMessageType::BOOMERANG_THROW_STATE);
		//プレイヤの状態とATTACKに
		SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_BOOMERANG_ATTACK_STATE);
		//プレイヤの構えの終了の通知
		SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_GET_REDAY_END);
		//ブーメランを投げた活動
		SceneMessenger::GetInstance()->Notify(SceneMessageType::BOOMERANG_THROW);


	}
}


/// <summary>
/// 状態に入った時
/// </summary>
void PlayerBoomerangGetReady::Enter()
{
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void PlayerBoomerangGetReady::Exit()
{
}
