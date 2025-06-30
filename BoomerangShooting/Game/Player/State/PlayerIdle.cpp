#include "pch.h"
#include "PlayerIdle.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Messenger/Scene/SceneMessages.h"


/// <summary>
/// コンストラクタ
/// </summary>
PlayerIdle::PlayerIdle(PlayerStateMachine* stateMachine, Player* player)
	:
	m_stateMahine{stateMachine}
	,m_player{player}
{



}

/// <summary>
/// デストラクタ
/// </summary>
PlayerIdle::~PlayerIdle()
{
}




/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlayerIdle::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	using namespace DirectX;

	const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();


	//左ボタンが押されたら
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		//通知
		//プレイヤの状態についての通知
		SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_BOOMERANG_GET_READY_STATE);
		//プレイヤの構えた活動に対しての通知
		SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_GET_REDAY);
		//ブーメランの状態を構えに
		SceneMessenger::GetInstance()->Notify(SceneMessageType::BOOMERANG_GET_READY_STATE);


	}





}


/// <summary>
/// 状態に入った時
/// </summary>
void PlayerIdle::Enter()
{



}

/// <summary>
/// 状態を抜けた時
/// </summary>
void PlayerIdle::Exit()
{
}



