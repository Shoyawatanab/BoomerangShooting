/*
敵を倒したときの敵をターゲットにしたカメラ
*/

#pragma once
#include "GameBase/Interface/IState.h"


class PlaySceneCamera;
class PlaySceneCameraStateMachine;


class PlaySceneCameraStop : public IState
{
public:

public:
	//コンストラクタ
	PlaySceneCameraStop(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera);
	//デストラクタ
	~PlaySceneCameraStop() override;

	// 更新する
	void Update(const float& deltaTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:
	//カメラ
	PlaySceneCamera* m_camera;
	//ステートマシーン
	PlaySceneCameraStateMachine* m_stateMAchine;


};
