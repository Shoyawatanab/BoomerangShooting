#include "pch.h"
#include "TitleSceneCamera.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene"></param>
TitleSceneCamera::TitleSceneCamera(Scene* scene)
	:
	Camera(scene)
	, m_angle{}
	
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleSceneCamera::~TitleSceneCamera()
{
}

/// <summary>
/// 個別カメラの更新処理
/// </summary>
/// <param name="deltaTime"></param>
void TitleSceneCamera::UpdateCamera(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	//回転
	m_angle += ROTATION_SPEED * deltaTime;
	
	float x = DISTANCE_TO_TARGET.x * cosf(m_angle);
	
	float z = DISTANCE_TO_TARGET.z * sinf(m_angle);

	Vector3 eye = DirectX::SimpleMath::Vector3(x, DISTANCE_TO_TARGET.y, z);

	SetEyePosition(eye);
}
