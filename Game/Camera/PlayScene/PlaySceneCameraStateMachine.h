/*
	クラス名     : PlaySceneCameraStateMachine
	説明         : プレイシーンカメラのステートマシーン
	補足・注意点 : 
*/
#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "Game/Messenger/Messengers.h"

class PlaySceneCamera;

//ステートの状態
enum class PlaySceneCameraState
{
	
	TPS              //TPSカメラ
	,ENEMY_TARGET	 //敵をターゲットにしたカメラ
	,STOP			 //停止カメラ
};

class PlaySceneCameraStateMachine : public StateMachine<IState, PlaySceneCameraState>
{

public:
	//コンストラクタ
	PlaySceneCameraStateMachine(PlaySceneCamera* camera);
	//デストラクタ
	~PlaySceneCameraStateMachine() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) ;


};
