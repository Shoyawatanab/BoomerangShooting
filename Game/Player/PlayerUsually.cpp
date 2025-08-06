/*
	クラス名     : PlayerUsually
	説明         : プレイヤの常に処理したもののクラス
	補足・注意点 :
*/
#include "pch.h"
#include "PlayerUsually.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"
#include "Game/Params.h"
#include "Game/Messenger/Messengers.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerUsually::PlayerUsually(Player* player)
	:
	m_player{ player }
	,m_rigidbody{}
	,m_moveDirection{}
	,m_isGetReady{false}
{
	//共通リソース
	m_commonResources = CommonResources::GetInstance();
	//重力
	m_rigidbody=  player->GetComponent<RigidbodyComponent>();
	m_rigidbody->SetDeceleration(Params::GRAUND_FRICTION);


	//通知を受け取るコンポーネントの追加
	auto ob = player->AddComponent<ObserverComponent<SceneMessageType>>(player);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::PLAYER_GET_REDAY
			,SceneMessageType::PLAYER_GET_REDAY_END
		}
		, std::bind(&PlayerUsually::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerUsually::~PlayerUsually()
{
}



/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerUsually::Update(const float& deltatime)
{
	using namespace DirectX::SimpleMath;


	//移動
	Move(deltatime);

	//回転
	Rotate(deltatime);

	CheckMouseWheel();

	m_moveDirection = Vector3::Zero;


}

/// <summary>
/// 通知受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void PlayerUsually::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::PLAYER_GET_REDAY:
			m_isGetReady = true;
			break;
		case SceneMessageType::PLAYER_GET_REDAY_END:
			m_isGetReady = false;
			break;
		default:
			break;
	}

}


/// <summary>
/// 移動
/// </summary>
void PlayerUsually::Move(const float& deltatime)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// キーボードステートを取得する
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	float moveSpeed = Params::PLAYER_MOVE_SPEED * deltatime;


	//カメラの横の回転軸から回転の計算
	Quaternion rotationX =Quaternion::CreateFromYawPitchRoll(m_player->GetPlaySceneCamera()->GetRotationY(),0.0f,0.0f);
	//カメラの回転に沿って回転
	m_moveDirection = Vector3::Transform(m_moveDirection, rotationX);
	m_moveDirection.Normalize();

	//移動
	m_rigidbody->AddForce(m_moveDirection * moveSpeed);

}

/// <summary>
/// 回転
/// </summary>
/// <param name="deltatime">経過時間</param>
void PlayerUsually::Rotate(const float& deltatime)
{
	using namespace DirectX::SimpleMath;

	if (!m_isGetReady)
	{
		Quaternion rotate = m_player->GetTransform()->GetRotate();
		//正面ベクトルの取得
		Vector3 playerForward = m_player->GetTransform()->GetForwardVector();
		//回転軸を求める
		Vector3 rotationAxis = m_moveDirection.Cross(playerForward);
		//軸がセロなら
		if (rotationAxis == Vector3::Zero)
		{
			return;
		}

		//値が小さい時は正規化しなう
		if (m_moveDirection.LengthSquared() > 0.0001f)
		{
			m_moveDirection.Normalize();
		}

		//軸の反転
		rotationAxis *= -1;
		//角度を求める
		float angle = Vector3::Distance(m_moveDirection, playerForward);

		angle *= deltatime * Params::PLAYER_ROTATION_SPEED;
		//回転を加算する
		Quaternion rotation = Quaternion::CreateFromAxisAngle(rotationAxis, angle);

		m_player->GetTransform()->SetRotate(m_player->GetTransform()->GetRotate() * rotation);
	}
	else
	{

		Quaternion rotationX = Quaternion::CreateFromYawPitchRoll(m_player->GetPlaySceneCamera()->GetRotationY() + DirectX::XM_PI, 0.0f, 0.0f);
		m_player->GetTransform()->SetRotate(rotationX);
	}

}

/// <summary>
/// マウスホイールのチェック
/// </summary>
void PlayerUsually::CheckMouseWheel()
{
	using namespace DirectX;

	const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	int scrollWheelValue = state.scrollWheelValue;

	//上に回転
	if (scrollWheelValue > 0)
	{
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::MOUSE_WHEEL_UP, nullptr);
	}
	//下に回転
	else if (scrollWheelValue < 0)
	{

		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::MOUSE_WHEEL_DOWN, nullptr);

	}
	//マウスホイールの移動値のリセット
	Mouse::Get().ResetScrollWheelValue();

}

/// <summary>
/// 入力時
/// </summary>
/// <param name="key"></param>
void PlayerUsually::OnInput(const DirectX::Keyboard::Keys& key)
{
	using namespace DirectX;

	switch (key)
	{
		case Keyboard::W:
			m_moveDirection.z--;
			break;
		case Keyboard::S:
			m_moveDirection.z++;
			break;
		case Keyboard::A:
			m_moveDirection.x--;
			break;
		case Keyboard::D:
			m_moveDirection.x++;
			break;
		default:
			break;
	}

}


