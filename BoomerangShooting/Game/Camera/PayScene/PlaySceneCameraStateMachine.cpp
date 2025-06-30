#include "pch.h"
#include "PlaySceneCameraStateMachine.h"
#include "PaySceneCameraStates.h"
#include "Game/Messenger/Scene/SceneMessages.h"


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

	//メッセンジャーに登録
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOSS_DEFEATED
			,SceneMessageType::GAME_OVER
		}, this
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
