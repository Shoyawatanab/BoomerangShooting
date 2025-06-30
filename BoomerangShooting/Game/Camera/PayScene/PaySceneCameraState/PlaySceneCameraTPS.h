#pragma once
#include "GameBase/Interface/IState.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class PlaySceneCamera;
class PlaySceneCameraStateMachine;

class PlaySceneCameraTPS : public IState , public IObserver<SceneMessageType>
{
public:
	//ズーム状態
	enum class ZoomState
	{
		NONE,             //通常
		ZOOM_IN,		  //ズーム状態
		ZOOM_OUT		  //ズームアウト状態
	};
public:
	//マウス座標
	static constexpr DirectX::SimpleMath::Vector2 MOUSE_POSITION{640.0f,320.0f};

	//マウス感度
	static constexpr float MOUSE_SENSITIVITY = 0.0005f;
	//カメラの限界角度
	static constexpr float ROTATE_LIMIT = 1.5f;

	// ターゲットからのデフォルト距離
	const float CAMERA_DISTANCE = 4.0f;

	//ズーム方向
	static constexpr DirectX::SimpleMath::Vector3 ZOOM_DIRECTION{0.2f, 0.0f, -1.0f};
	//ズームにかかる時間
	static constexpr float ZOOME_MAX_TIME = 0.2f;;

public:
	//コンストラクタ
	PlaySceneCameraTPS(PlaySceneCameraStateMachine* stateMachine,PlaySceneCamera* camera);
	//デストラクタ
	~PlaySceneCameraTPS() override;

	// 更新する
	void Update(const float& deltaTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

	//通知を受け取る関数
	void Notify(SceneMessageType type, void* datas) override;


private:

	//マウス操作
	void MouseOperation();
	//ズームの更新
	void ZoomUpdate(const float& deltaTime);

	//揺れ
	void Shake(const float& deltaTime);

private:
	//カメラ
	PlaySceneCamera* m_camera;
	//ステートマシーン
	PlaySceneCameraStateMachine* m_stateMAchine;
	//横回転
	float m_rotationX;
	//縦回転
	float m_rotationY;
	//ズーム状態
	ZoomState m_zoomState;
	//ズームの移動量
	DirectX::SimpleMath::Vector3 m_zoomMovement;
	//ズーム時間
	float m_zoomTime;

};