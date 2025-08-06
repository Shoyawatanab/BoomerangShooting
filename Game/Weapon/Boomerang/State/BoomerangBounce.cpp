/*
	クラス名     : BoomerangBounce
	説明         : ブーメランの跳ね返りの状態
	補足・注意点 :
*/
#include "pch.h"
#include "BoomerangBounce.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stateMahine">ステートマシーン</param>
/// <param name="boomerang">ブーメラン</param>
/// <param name="player">プレイヤ</param>
BoomerangBounce::BoomerangBounce(BoomerangStateMachine* stateMahine, Boomerang* boomerang)
	:
	m_stateMahine{ stateMahine }
	, m_boomerang{ boomerang }
	,m_bounceDirection{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangBounce::~BoomerangBounce()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangBounce::Update(const float& deltaTime)
{

	auto position = m_boomerang->GetTransform()->GetWorldPosition();

	position += m_bounceDirection * BOUNCE_POWER *  deltaTime;

	m_boomerang->GetTransform()->SetPosition(position);


}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangBounce::Enter()
{
	//リジットボディーの有効
	m_boomerang->GetComponent<RigidbodyComponent>()->SetActive(true);
	//跳ね返り方向を求める
	m_bounceDirection = m_boomerang->GetTransform()->GetWorldPosition() - m_boomerang->GetLastPosition();

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangBounce::Exit()
{
}
