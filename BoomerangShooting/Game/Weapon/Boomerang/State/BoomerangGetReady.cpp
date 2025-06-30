#include "pch.h"
#include "BoomerangGetReady.h"
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
BoomerangGetReady::BoomerangGetReady(BoomerangStateMachine* stateMahine, Boomerang* boomerang, Player* player)
	:
	m_stateMahine{ stateMahine }
	, m_boomerang{ boomerang }
	, m_player{ player }
{
}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangGetReady::~BoomerangGetReady()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangGetReady::Update(const float& deltaTime)
{



}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangGetReady::Enter()
{
	//ローカル回転の設定
	m_boomerang->GetTransform()->SetRotate(Params::BOOMERANG_GETREADY_ROTATION);
	//ローカル座標の設定
	m_boomerang->GetTransform()->SetPosition(Params::BOOMERANG_GETREADY_POSITION);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangGetReady::Exit()
{
}
