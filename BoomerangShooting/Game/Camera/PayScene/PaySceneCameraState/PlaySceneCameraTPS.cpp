#include "pch.h"
#include "PlaySceneCameraTPS.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Player/Player.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stateMachine">ステートマシーン</param>
/// <param name="camera">カメラ</param>
PlaySceneCameraTPS::PlaySceneCameraTPS(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera)
	:
	m_camera{camera}
	,m_stateMAchine{stateMachine}
	,m_rotationX{}
	,m_rotationY{}
	,m_zoomState{}
	,m_zoomMovement{}
	,m_zoomTime{}
{

	//メッセンジャーに登録
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_GET_REDAY
			,SceneMessageType::PLAYER_GET_REDAY_END
		}
		, this
	);


}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneCameraTPS::~PlaySceneCameraTPS()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlaySceneCameraTPS::Update(const float& deltaTime)
{
	using namespace DirectX;;
	using namespace DirectX::SimpleMath;

	//マウス操作
	MouseOperation();
	//ズームの更新
	ZoomUpdate(deltaTime);
	//ターゲット
	Vector3 target = m_camera->GetTarget()->GetTransform()->GetWorldPosition() +  Vector3(0, 1, 0);
	//X軸回転の計算
	Quaternion rotateX = Quaternion::CreateFromAxisAngle(Vector3::UnitY, XMConvertToRadians(m_rotationX));
	//回転の計算
	Quaternion rotate = Quaternion::CreateFromYawPitchRoll(m_rotationY, m_rotationX, 0.0f);
	// カメラがターゲットからどれくらい離れているか
	Vector3 eye = Vector3::UnitZ * CAMERA_DISTANCE;
	//視点の回転
	eye = Vector3::Transform(eye, rotate);
	eye += target;

	//ズーム時の回転
	Vector3 movemement = Vector3::Transform(m_zoomMovement, rotate);

	//カメラにセット
	m_camera->SetEyePosition(eye + movemement);
	m_camera->SetTargetPosition(target);

	//正面ベクトル
	Vector3 forward = target - eye;
	forward.Normalize();
	m_camera->SetForwardVector(forward);

}

/// <summary>
/// 状態にはいいた時
/// </summary>
void PlaySceneCameraTPS::Enter()
{
	//初期値設定
	SetCursorPos(MOUSE_POSITION.x,MOUSE_POSITION.y);
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_zoomTime = 0.0f;
	m_zoomState = ZoomState::NONE;

	ShowCursor(false);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void PlaySceneCameraTPS::Exit()
{
	ShowCursor(true);

}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void PlaySceneCameraTPS::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::PLAYER_GET_REDAY:
			m_zoomState = ZoomState::ZOOM_IN;
			m_zoomTime = 0.0f;
			break;
		case SceneMessageType::PLAYER_GET_REDAY_END:
			m_zoomState = ZoomState::ZOOM_OUT;
			m_zoomMovement = DirectX::SimpleMath::Vector3::Zero;
			m_zoomTime = 0.0f;

			break;

		default:
			break;
	}

}

/// <summary>
/// マウス操作
/// </summary>
void PlaySceneCameraTPS::MouseOperation()
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//マウス座標変数
	POINT mousePosition;
	//マウス座標の取得
	GetCursorPos(&mousePosition);
	//差分を求める
	Vector2 diff;
	diff.x = MOUSE_POSITION.x - mousePosition.x;
	diff.y = MOUSE_POSITION.y - mousePosition.y;
	//移動量の加算
	m_rotationX += diff.y * MOUSE_SENSITIVITY;
	m_rotationY += diff.x * MOUSE_SENSITIVITY;

	//初期値設定
	SetCursorPos(MOUSE_POSITION.x, MOUSE_POSITION.y);
	//上の制限
	if (m_rotationX >= ROTATE_LIMIT)
	{
		m_rotationX = ROTATE_LIMIT;
	}
	//下の制限
	if (m_rotationX <= -ROTATE_LIMIT)
	{
		m_rotationX = -ROTATE_LIMIT;
	}

	//プレイカメラにセット
	m_camera->SetRotationX(m_rotationX);
	m_camera->SetRotationY(m_rotationY );
}

/// <summary>
/// ズームの更新
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlaySceneCameraTPS::ZoomUpdate(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	if (m_zoomState == ZoomState::NONE)
	{
		return;
	}

	//初期化
	m_zoomMovement = Vector3::Zero;

	//進行割合
	float ratio = m_zoomTime / ZOOME_MAX_TIME;

	ratio = std::min(ratio, 1.0f);

	switch (m_zoomState)
	{
		case PlaySceneCameraTPS::ZoomState::NONE:
			break;
		case PlaySceneCameraTPS::ZoomState::ZOOM_IN:

			m_zoomMovement = Vector3::Lerp(
				Vector3::Zero, ZOOM_DIRECTION
				,ratio
				);

			break;
		case PlaySceneCameraTPS::ZoomState::ZOOM_OUT:
			m_zoomMovement = Vector3::Lerp(
				ZOOM_DIRECTION,Vector3::Zero
				, ratio
			);
			break;
		default:
			break;
	}


	m_zoomTime += deltaTime;
}

/// <summary>
/// 画面の揺れ
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlaySceneCameraTPS::Shake(const float& deltaTime)
{

	//using namespace DirectX::SimpleMath;
	//
	//if (!m_isShake)
	//{
	//	return;
	//}


	//m_shaleTime -= deltaTime;


	//if (m_shaleTime <= 0.0f)
	//{
	//	m_isShake = false;
	//	m_shakePosition = Vector3::Zero;
	//	return;
	//}

	//float power = (m_shaleTime / SHAKETIME) * m_shakePower;

	////	完全なランダムをハードウェア的に生成するためのクラスの変数
	//std::random_device seed;
	////	上記の完全なランダムは動作が遅いため、seed値の決定のみに使用する
	////	※「default_random_engine」はusingで「mt19937」となっている
	//std::default_random_engine engine(seed());
	////	生成して欲しいランダムの範囲をDistributionに任せる。今回は0～2PI
	//std::uniform_real_distribution<> dist(-power, power);

	//float x = static_cast<float>(dist(engine));
	//float y = static_cast<float>(dist(engine));
	//float z = static_cast<float>(dist(engine));

	//m_shakePosition = Vector3(x, y, z);


}
