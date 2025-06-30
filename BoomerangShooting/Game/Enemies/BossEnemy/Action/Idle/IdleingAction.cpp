#include "pch.h"
#include "IdleingAction.h"



/// <summary>
/// コンストラクタ
/// </summary>
IdleingAction::IdleingAction()
{



}

/// <summary>
/// デストラクタ
/// </summary>
IdleingAction::~IdleingAction()
{
	// do nothing.
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
IdleingAction:: ActionState IdleingAction::Update(const float& elapsedTime)
{

	return ActionState::END;

}


/// <summary>
/// 状態に入った時
/// </summary>
void IdleingAction::Enter()
{

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void IdleingAction::Exit()
{
}
