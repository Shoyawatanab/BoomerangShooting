/*
	@file	OrientationAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "OrientationAction.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"
#include "GameBase/Component/Components.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
OrientationAction::OrientationAction(Actor* own
	, Actor* target)
	:
	m_commonResources{}
	,m_own{own}
	,m_target{target}
{
	m_commonResources = CommonResources::GetInstance();


}

/// <summary>
/// デストラクタ
/// </summary>
OrientationAction::~OrientationAction()
{
	// do nothing.
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
OrientationAction:: ActionState OrientationAction::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	auto ownerPosition = m_own->GetTransform()->GetPosition();

	auto targetPosition = m_target->GetTransform()->GetPosition();

	ownerPosition.y = 0.0f;
	targetPosition.y = 0.0f;

	//向きたい方向
	Vector3 direction = targetPosition - ownerPosition;
	direction.Normalize();
	//今の敵の前方向
	Vector3 forward = m_own->GetTransform()->GetForwardVector();
	//forward.Normalize();
	//回転軸の作成
	Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//正なら上方向
		moveAxis = Vector3::Up;
	}
	else
	{
		//負なら下方向
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(direction);


	//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * elapsedTime);

	//敵の回転の取得
	DirectX::SimpleMath::Quaternion Rotate = m_own->GetTransform()->GetRotate();
	//Y軸に対して回転をかける
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_own->GetTransform()->SetRotate(Rotate);


	//// 敵の今の前方向を更新
	forward = m_own->GetTransform()->GetForwardVector();
	forward.Normalize();

	// プレイヤー方向との差を再計算
	float alignment = forward.Dot(direction);

	// 角度が小さい（向けている）なら追加処理
	const float threshold = cosf(DirectX::XMConvertToRadians(Params::ENEMY_PERMISSIBLE_ANGLE)); // 5度以内ならOKとする

	if (alignment >= threshold)
	{
		return ActionState::END;
	}



	return ActionState::RUNNING;


}


/// <summary>
/// 状態に入った時
/// </summary>
void OrientationAction::Enter()
{


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void OrientationAction::Exit()
{
}
