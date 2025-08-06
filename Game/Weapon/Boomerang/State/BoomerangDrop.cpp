/*
	クラス名     : BoomerangDrop
	説明         : ブーメランのドロップの状態
	補足・注意点 :
*/
#include "pch.h"
#include "BoomerangDrop.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stateMahine">ステートマシーン</param>
/// <param name="boomerang">ブーメラン</param>
/// <param name="player">プレイヤ</param>
BoomerangDrop::BoomerangDrop(BoomerangStateMachine* stateMahine, Boomerang* boomerang)
	:
	m_stateMahine{ stateMahine }
	, m_boomerang{ boomerang }
{
}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangDrop::~BoomerangDrop()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangDrop::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangDrop::Enter()
{
	//リジットボディーの有効
	m_boomerang->GetComponent<RigidbodyComponent>()->SetActive(false);
	m_boomerang->GetComponent<PickableComponent>()->SetIsPossible(true);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangDrop::Exit()
{
	m_boomerang->GetComponent<PickableComponent>()->SetIsPossible(false);

}
