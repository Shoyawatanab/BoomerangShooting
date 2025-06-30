#pragma once
#include "GameBase/Camera/Camera.h"

class TitleSceneCamera : public Camera
{
public:

	//ターゲットまでの距離
	static constexpr DirectX::SimpleMath::Vector3 DISTANCE_TO_TARGET{6.0f, 4.0f, 6.0f};

	static constexpr float ROTATION_SPEED = 0.25f;

public:
	//
	TitleSceneCamera(Scene* scene);
	//
	~TitleSceneCamera();

	void UpdateCamera(const float& deltaTime) override;

private:
	//角度
	float m_angle;

};