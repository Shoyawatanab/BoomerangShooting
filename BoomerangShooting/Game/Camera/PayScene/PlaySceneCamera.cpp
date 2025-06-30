#include "pch.h"
#include  "PlaySceneCamera.h"
#include "GameBase/Component/Components.h"
#include "PlaySceneCameraStateMachine.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
PlaySceneCamera::PlaySceneCamera(Scene* scene)
	:
	Camera(scene)
	,m_stateMachine{}
	, m_rotationX{}
	, m_rotationY{}
{


	//ステートマシーンの作成
	m_stateMachine = std::make_unique<PlaySceneCameraStateMachine>(this);


}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneCamera::~PlaySceneCamera()
{
	ShowCursor(true);

}



/// <summary>
/// カメラの個別更新処理
/// </summary>
/// <param name="deltaTime"></param>
void PlaySceneCamera::UpdateCamera(const float& deltaTime)
{
	//ステートマシーンの更新
	m_stateMachine->Update(deltaTime);

}


