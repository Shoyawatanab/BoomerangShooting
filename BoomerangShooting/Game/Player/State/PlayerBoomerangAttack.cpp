#include "pch.h"
#include "PlayerBoomerangAttack.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Messenger/Scene/SceneMessages.h"


/// <summary>
/// コンストラクタ
/// </summary>
PlayerBoomerangAttack::PlayerBoomerangAttack(PlayerStateMachine* stateMachine, Player* player)
	:
	m_stateMahine{stateMachine}
	,m_player{player}
	,m_throwState{}
	,m_throwQuantityState{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBoomerangAttack::~PlayerBoomerangAttack()
{
}



/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlayerBoomerangAttack::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	using namespace DirectX;


	
}



/// <summary>
/// 状態に入った時
/// </summary>
void PlayerBoomerangAttack::Enter()
{
	//プレイヤの状態を通常に
	SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_IDLE_STATE);

}


/// <summary>
/// 状態を抜けた時
/// </summary>
void PlayerBoomerangAttack::Exit()
{


}





