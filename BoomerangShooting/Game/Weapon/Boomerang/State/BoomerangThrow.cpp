#include "pch.h"
#include "BoomerangThrow.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/Player.h"
#include "Game/MathUtil.h"
#include "Libraries/WataLib/CSV.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Camera/Camera.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/UI/PlayScene/TargetMarker/TargetMarker.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stateMahine">ステートマシーン</param>
/// <param name="boomerang">ブーメラン</param>
/// <param name="player">プレイヤ</param>
BoomerangThrow::BoomerangThrow(BoomerangStateMachine* stateMahine, Boomerang* boomerang, Player* player)
	:
	m_stateMahine{ stateMahine }
	, m_boomerang{ boomerang }
	,m_player{player}
	,m_throwbasePosition{}
	,m_totalTime{}
	,m_index{}
	,m_state{}
{

	//CSVから基準座標の取得
	m_throwbasePosition = WataLib::CSV::LoadCSVBoomerang();


}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangThrow::~BoomerangThrow()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangThrow::Update(const float& deltaTime)
{

	//回転
	Rotation(deltaTime);

	switch (m_state)
	{
		case BoomerangThrow::State::SPINECURVE:		
			SplineCurve(deltaTime);
			break;
		case BoomerangThrow::State::CHASE_TO_PLAYER:
			ChaseToPlayer(deltaTime);
			break;
		default:
			break;
	}

}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangThrow::Enter()
{
	using namespace DirectX::SimpleMath;

	m_boomerang->GetTransform()->SetParent(nullptr);


	//基準点の作成
	CreateSplineCurvePositon();

	//初期化
	m_index = 0;
	m_horizontalRotation = Quaternion::Identity;
	m_state = State::SPINECURVE;

	//回転の情報を切り替える
	ChangeRotationDatas(Params::BOOMERANG_THROW_START_ROTATION, Params::BOOMERANG_THROW_MIDDLE_ROTATION);

	//初期回転をプレイヤの回転に
	m_initialRotation = m_player->GetTransform()->GetRotate();
	//当たり判定の有効
	auto aabb = m_boomerang->GetComponent<AABB>();
	aabb->SetActive(true);
	//影の有効
	auto shadow = m_boomerang->GetComponent<RoundShadowComponent>();
	shadow->SetActive(true);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangThrow::Exit()
{
	//当たり判定の無効
	auto aabb = m_boomerang->GetComponent<AABB>();
	aabb->SetActive(false);
	//影の無効
	auto shadow = m_boomerang->GetComponent<RoundShadowComponent>();
	shadow->SetActive(false);


}

void BoomerangThrow::CreateSplineCurvePositon()
{
	using namespace DirectX::SimpleMath;

	std::vector<DirectX::SimpleMath::Vector3> basePosition = m_throwbasePosition;

	//ターゲットの取得
	Vector3 target;

	//ロックオンしていたら
	if (m_player->GetTargetMarker()->GetIsGetLockOn())
	{

		//ロックオンしている敵の座標に
		target = m_player->GetTargetMarker()->GetTargetPosition();

	}
	else
	{

		target = m_boomerang->GetScene()->GetCamera()->GetForwardVector();

		target.Normalize();

		target *= TARGET_LENGTH;

		target += m_player->GetTransform()->GetWorldPosition();

	}


	//ブーメランからターゲットまでの距離
	Vector3 boomerangToTargetDistance = target - m_boomerang->GetTransform()->GetPosition();


	float boomerangToTargetLenght = boomerangToTargetDistance.Length();

	boomerangToTargetDistance = Vector3(0, 0, -1) * boomerangToTargetLenght;

	//値を正に
	boomerangToTargetDistance.x = std::abs(boomerangToTargetDistance.x);
	//boomerangToTargetDistance.y =std::abs(boomerangToTargetDistance.y);
	boomerangToTargetDistance.z = std::abs(boomerangToTargetDistance.z);

	//高さをゼロに
	boomerangToTargetDistance.y = 0.0f;
	//float型に変換　長さを半分に
	float boomerangToTargetHalfLenght = boomerangToTargetDistance.Length() / 2;

	//基準点を変更
	for (int i = 0; i < basePosition.size(); i++)
	{

		//基準点から中心までの長さを求める
		float lenght = basePosition[i].Length();
		//割合を求める
		float ratio = (lenght == 0.0f) ? 0.0f : boomerangToTargetHalfLenght / lenght;
		//割合をもとに基準点を変更
		basePosition[i] *= ratio;

		basePosition[i] -= boomerangToTargetDistance / 2;

	}

	for (int i = 0; i < basePosition.size(); i++)
	{

		//一番遠い基準点との割合を求める
		float ratio = basePosition[i].z / basePosition[basePosition.size() / 2].z;
		//高さの調整
		basePosition[i].y = MathUtil::Lerp(m_boomerang->GetTransform()->GetPosition().y, target.y, ratio);

	}

	//基準点の初期観点とプレイヤの回転　　　	基準点が180度ずれているため
	Quaternion rotation = Params::BOOMERANG_THROW_POINT_ROTATE *  m_player->GetTransform()->GetRotate()  ;

	for (int i = 0; i < basePosition.size(); i++)
	{
		//プレイヤの回転に合わせる
		basePosition[i] = Vector3::Transform(basePosition[i], rotation);
		//プレイヤの座標を加算する
		basePosition[i].x += m_boomerang->GetTransform()->GetPosition().x;
		basePosition[i].z += m_boomerang->GetTransform()->GetPosition().z;
	}


	m_splineCurvePosition = basePosition;



}

/// <summary>
/// スプライン曲線
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BoomerangThrow::SplineCurve(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;
	//座標の距離を求める
	float distance = (m_splineCurvePosition[(m_index + 1) % m_splineCurvePosition.size()]
		- m_splineCurvePosition[(m_index) % m_splineCurvePosition.size()]).Length();


	//割合を求める
	float ratio = m_totalTime * Params::BOOMERANG_MOVE_SPEED / distance;

	//スプライン曲線を使用して座標を求める
	Vector3 position = Vector3::CatmullRom(
		m_splineCurvePosition[(m_index - 1) % m_splineCurvePosition.size()],
		m_splineCurvePosition[(m_index + 0) % m_splineCurvePosition.size()],
		m_splineCurvePosition[(m_index + 1) % m_splineCurvePosition.size()],
		m_splineCurvePosition[(m_index + 2) % m_splineCurvePosition.size()],
		ratio
	);

	//座標の登録
	m_boomerang->GetTransform()->SetPosition(position);


	if (ratio > 1.0f)
	{
		//次の点と点に変更
		m_index++;
		m_totalTime = 0.0f;

		//半分まで行ったら
		if ((m_index) % m_splineCurvePosition.size() == m_splineCurvePosition.size() / 2)
		{
			ChangeRotationDatas(Params::BOOMERANG_THROW_MIDDLE_ROTATION, Params::BOOMERANG_THROW_END_ROTATION);
		}

		//最後の基準点に来たら
		if ((m_index) % m_splineCurvePosition.size() == m_splineCurvePosition.size() - 1)
		{
			m_state = State::CHASE_TO_PLAYER;
		}
	}

	//経過時間の加算
	m_totalTime += deltaTime;

}

/// <summary>
/// プレイヤを追いかける
/// </summary>
/// <param name="deltaTime"></param>
void BoomerangThrow::ChaseToPlayer(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	//ブーメランの座標を取得
	DirectX::SimpleMath::Vector3 BoomerangPos = m_boomerang->GetTransform()->GetPosition();
	//プレイヤの座標を取得
	DirectX::SimpleMath::Vector3 PlayerPos = m_player->GetTransform()-> GetPosition();


	//進む方向
	m_moveDirection = PlayerPos - BoomerangPos;
	m_moveDirection.Normalize();
	//どれだけ移動するか求める
	Vector3 moveDirection = m_moveDirection * Params::BOOMERANG_MOVE_SPEED * deltaTime;
	//移動値の加算
	BoomerangPos += moveDirection;
	//座標の登録
	m_boomerang->GetTransform()->SetPosition(BoomerangPos);

	//プレイヤとの距離を求める
	float distance = (PlayerPos - BoomerangPos).Length();

	//近づいたら
	if (distance <= 0.3f)
	{

		//ブーメランの状態を通常に
		m_boomerang->GetStateMAchine()->ChangeState(BoomerangState::IDEL);
		//ブーメランのキャッチの活動
		SceneMessenger::GetInstance()->Notify(SceneMessageType::BOOMERANG_CATCH);

	}


}


/// <summary>
/// 回転
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BoomerangThrow::Rotation(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;
	//横回転
	m_horizontalRotation *= Quaternion::CreateFromAxisAngle(Vector3::Up, Params::BOOMERANG_HORIZONTAL_ROTATION_SPEED * deltaTime);

	//斜めの回転
	Quaternion rotation;
	//スタート地点から中間地点までのベクトル
	Vector3 startToMidleVec = m_splineCurvePosition[m_splineCurvePosition.size() / 2] - m_splineCurvePosition[0];
	startToMidleVec.Normalize();
	//スタート地点からブーメランまでのベクトル
	Vector3 startToBoomerangVec = m_boomerang->GetTransform()->GetPosition() - m_splineCurvePosition[0];
	//投影ベクトル
	Vector3 projectionVec = startToMidleVec * startToBoomerangVec.Dot(startToMidleVec);

	Vector3 pos = m_splineCurvePosition[0] + projectionVec;

	float distance = Vector3::Distance(m_splineCurvePosition[0], pos);
	//割合を求める
	float ratio = distance / Vector3::Distance(m_splineCurvePosition[m_splineCurvePosition.size() / 2], m_splineCurvePosition[0]);
	ratio = std::min(ratio, 1.0f);
	//斜めの回転を求める
	rotation = Quaternion::Lerp(m_rotationDatas.first, m_rotationDatas.second, ratio);
	//回転の設定　横の回転　斜めの回転　初期の回転
	m_boomerang->GetTransform()->SetRotate(m_horizontalRotation * rotation * m_initialRotation);

}

/// <summary>
/// 回転データの切り替え
/// </summary>
/// <param name="firstVec">初期値</param>
/// <param name="secondVec">終了値</param>
void BoomerangThrow::ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec)
{
	m_rotationDatas.first = firstVec;
	m_rotationDatas.second = secondVec;

}
