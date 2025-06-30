#include "pch.h"
#include "PlayerUsually.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"


#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"

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

	m_rigidbody=  player->GetComponent<RigidbodyComponent>();
	m_rigidbody->SetDeceleration(Params::GRAUND_FRICTION);


	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_GET_REDAY
			,SceneMessageType::PLAYER_GET_REDAY_END
		}
		, this);
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

	m_moveDirection = Vector3::Zero;

	//移動
	Move(deltatime);

	//回転
	Rotate(deltatime);




}

/// <summary>
/// 通知受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void PlayerUsually::Notify(SceneMessageType type, void* datas)
{
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

	Transform* transform = m_player->GetTransform();

	float moveSpeed = Params::PLAYER_MOVE_SPEED * deltatime;


	if (key.IsKeyDown(Keyboard::Keyboard::W))
	{
		m_moveDirection.z--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::S))
	{
		m_moveDirection.z++;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::A))
	{
		m_moveDirection.x--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::D))
	{
		m_moveDirection.x++;
	}

	//カメラの横の回転軸から回転の計算
	Quaternion rotationX =Quaternion::CreateFromYawPitchRoll(m_player->GetPlaySceneCamera()->GetRotationY(),0.0f,0.0f);
	//カメラの回転に沿って回転
	m_moveDirection = Vector3::Transform(m_moveDirection, rotationX);

	//移動
	m_rigidbody->AddForce(m_moveDirection * moveSpeed);

}

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



