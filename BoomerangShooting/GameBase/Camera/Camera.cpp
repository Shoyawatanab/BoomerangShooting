#include "pch.h"
#include "Camera.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Screen.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
Camera::Camera(Scene* scene)
	:
	Actor(scene)
	,m_eye{DirectX::SimpleMath::Vector3::UnitZ}
	,m_target{DirectX::SimpleMath::Vector3::Zero}
	,m_up{DirectX::SimpleMath::Vector3::Up}
	,m_view{}
	,m_projection{}
	,m_forwardVector{ DirectX::SimpleMath::Vector3::Forward }

{

	using namespace DirectX::SimpleMath;

	//ビュー行列の計算
	m_view = Matrix::CreateLookAt(m_eye, m_target, m_up);


	//プロジェクション行列計算
	RECT rect{ 0,0,Screen::WIDTH,Screen::HEIGHT };
	using namespace DirectX;
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 150.0f
	);



}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Camera::Update(const float& deltaTime)
{

	
	//カメラの個別更新処理
	UpdateCamera(deltaTime);

	//ビュー行列の計算
	CalculateViewMatrix();

}



/// <summary>
/// ビュー行列の計算
/// </summary>
void Camera::CalculateViewMatrix()
{

	using namespace DirectX::SimpleMath;

	//ビュー行列の計算
	m_view = Matrix::CreateLookAt(m_eye, m_target, m_up);

}
