/*
	@file	WalkAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "WalkAction.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "GameBase/Common/Commons.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
WalkAction::WalkAction(BossEnemy* own
	, Actor* target)
	:
	m_own{own}
	,m_target{target}
	,m_time{}
{

	m_commonResources = CommonResources::GetInstance();

}

/// <summary>
/// デストラクタ
/// </summary>
WalkAction::~WalkAction()
{
	// do nothing.
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
WalkAction:: ActionState WalkAction::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	auto animation = m_own->GetAnimation();

	animation->SetFloat("Move", 1.0f);

//回転
	//向きたい方向
	Vector3 direction = m_target->GetTransform()->GetPosition() - m_own->GetTransform()->GetPosition();
	direction.Normalize();
	//今の敵の前方向
	Vector3 forward = Vector3::Transform(Vector3::Backward, m_own->GetTransform()->GetRotate());
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
		moveAxis = Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(direction);


	//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * elapsedTime);

	//敵の回転の取得
	Quaternion Rotate = m_own->GetTransform()->GetRotate();
	//Y軸に対して回転をかける
	Rotate *= Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_own->GetTransform()->SetRotate(Rotate);


//移動
	//プレイヤの座標の取得
	Vector3 targetPosition = m_target->GetTransform()->GetPosition();

	Vector3 ownPosition = m_own->GetTransform()->GetPosition();

	//方向を求める
	direction = targetPosition - ownPosition;
	//正規化
	direction.Normalize();

	direction *= Params::BOSSENEMY_MOVE_SPEED * elapsedTime;

	m_own->GetTransform()->SetPosition(ownPosition + direction);

	//アニメーションの時間に合わせる
	if (m_time >= WALK_TIME)
	{
		return ActionState::END;
	}

	m_time += elapsedTime;

	return ActionState::RUNNING;

}


/// <summary>
/// 状態に入った時
/// </summary>
void WalkAction::Enter()
{
	m_time = 0;
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void WalkAction::Exit()
{
}
