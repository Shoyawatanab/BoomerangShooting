#include "pch.h"
#include "Boomerangidle.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Player/Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stateMahine">ステートマシーン</param>
/// <param name="boomerang">ブーメラン</param>
/// <param name="player">プレイヤ</param>
BoomerangIdle::BoomerangIdle(BoomerangStateMachine* stateMahine, Boomerang* boomerang, Player* player)
	:
	m_stateMahine{stateMahine}
	,m_boomerang{boomerang}
	,m_player{player}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangIdle::~BoomerangIdle()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangIdle::Update(const float& deltaTime)
{



}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangIdle::Enter()
{
	//親の設定
	m_boomerang->GetTransform()->SetParent(m_player->GetTransform());
	//各パラメーター設定
	m_boomerang->GetTransform()->SetPosition(Params::BOOMERANG_IDLE_POSITION);
	m_boomerang->GetTransform()->SetRotate(Params::BOOMERANG_IDLE_ROTATION);
	m_boomerang->GetTransform()->SetScale(Params::BOOMERANG_IDLE_SCALE);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangIdle::Exit()
{
}
