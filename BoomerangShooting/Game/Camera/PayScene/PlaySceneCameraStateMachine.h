#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class PlaySceneCamera;


enum class PlaySceneCameraState
{
	
	TPS              //TPSカメラ
	,ENEMY_TARGET	 //敵をターゲットにしたカメラ
	,STOP			 //停止カメラ
};

class PlaySceneCameraStateMachine : public StateMachine<IState, PlaySceneCameraState> , public IObserver<SceneMessageType>
{

public:
	//コンストラクタ
	PlaySceneCameraStateMachine(PlaySceneCamera* camera);
	//デストラクタ
	~PlaySceneCameraStateMachine() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) override;


};
