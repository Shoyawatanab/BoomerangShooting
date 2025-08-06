/*
	クラス名     : PlaySceneCameraStateMachine
	説明         : プレイシーンカメラのステートマシーン
	補足・注意点 :
*/
#include "pch.h"
#include "PlaySceneCameraStateMachine.h"
#include "PlaySceneCameraStates.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="camera"></param>
PlaySceneCameraStateMachine::PlaySceneCameraStateMachine(PlaySceneCamera* camera)
{
	//各ステートの追加
	AddState(PlaySceneCameraState::TPS, std::make_unique<PlaySceneCameraTPS>(this,camera));
	AddState(PlaySceneCameraState::ENEMY_TARGET, std::make_unique<PlaySceneEnemyTargetCamera>(this,camera));
	AddState(PlaySceneCameraState::STOP, std::make_unique<PlaySceneCameraStop>(this,camera));

	//初期ステートの設定
	SetStartState(PlaySceneCameraState::TPS);


	//通知を受け取るコンポーネントの追加
	auto ob = camera->AddComponent<ObserverComponent<SceneMessageType>>(camera);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::BOSS_DEFEATED
			,SceneMessageType::GAME_OVER
		}
		, std::bind(&PlaySceneCameraStateMachine::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);
}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneCameraStateMachine::~PlaySceneCameraStateMachine()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void PlaySceneCameraStateMachine::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);
	switch (type)
	{
		case SceneMessageType::BOSS_DEFEATED:
			ChangeState(PlaySceneCameraState::ENEMY_TARGET);
			break;
		case SceneMessageType::GAME_OVER:
			ChangeState(PlaySceneCameraState::STOP);
			break;
		default:
			break;
	}
}
