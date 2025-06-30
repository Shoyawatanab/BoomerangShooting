#pragma once
#include "GameBase/Actor.h"


class Camera : public Actor
{

public:

	//視点の取得
	const DirectX::SimpleMath::Vector3& GetEyePosition() { return m_eye; }
	//視点のセット
	void SetEyePosition(const DirectX::SimpleMath::Vector3& eye) { m_eye = eye; }
	//注視点の取得
	const DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_target; }
	//注視点のセット
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& target) { m_target = target; }
	//頭の方向の取得
	const DirectX::SimpleMath::Vector3& GetUpPosition() { return m_up; }
	//頭の方向のセット
	void SetUpPosition(const DirectX::SimpleMath::Vector3& up) { m_up = up; }
	//ビュー行列の取得
	const DirectX::SimpleMath::Matrix& GetViewMatrix() const  { return m_view; }
	//射影行列の取得
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }
	//正面ベクトルの取得
	const DirectX::SimpleMath::Vector3& GetForwardVector() { return m_forwardVector; }
	//正面ベクトルのセット
	void SetForwardVector(const DirectX::SimpleMath::Vector3& forwardVector) { m_forwardVector = forwardVector; }

public:
	//コンストラクタ
	Camera(Scene* scene);
	//デストラクタ
	~Camera() override ;

	// 更新処理
	void Update(const float& deltaTime);

	//カメラの個別更新処理
	virtual void UpdateCamera(const float& deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };

	// ビュー行列の計算
	void CalculateViewMatrix();

private:

	//視点
	DirectX::SimpleMath::Vector3 m_eye;
	//注視点
	DirectX::SimpleMath::Vector3 m_target;
	//頭の方向
	DirectX::SimpleMath::Vector3 m_up;
	//ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	//射影行列
	DirectX::SimpleMath::Matrix m_projection;

	//カメラの正面ベクトル
	DirectX::SimpleMath::Vector3 m_forwardVector;

};

