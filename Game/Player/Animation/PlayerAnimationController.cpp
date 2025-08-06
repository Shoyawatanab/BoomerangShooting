/*
	クラス名     : PlayerAnimationController
	説明         : プレイヤアニメーションコントローラー
	補足・注意点 :
*/
#include "pch.h"
#include "PlayerAnimationController.h"
#include "Game/Player/Player.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player"></param>
PlayerAnimationController::PlayerAnimationController(Player* player)
	:
	AnimationController()
{
	//パーツ情報の取得
	auto partss = player->GetPlayerModel()->GetParts();


	//名前とトランスフォームのペアの作成
	//格納変数
	std::vector<std::pair<std::string,Actor*>> data;

	for (auto& parts : partss)
	{
		//名前とトランスフォームの追加
		data.push_back(std::make_pair(parts.first,parts.second));
	}
		
	
	
	//各Animationの作成
	AddAnimatoin(player,"PlayerIdle","Resources/Json/PlayerData/Animation/PlayerIdle.json",data,true);
	AddAnimatoin(player,"PlayerMove","Resources/Json/PlayerData/Animation/PlayerMove.json",data);
	AddAnimatoin(player,"PlayerGetReady","Resources/Json/PlayerData/Animation/PlayerBoomerangGetReady.json",data);
	AddAnimatoin(player,"PlayerThrow","Resources/Json/PlayerData/Animation/PlayerBoomerangThrow.json",data);
	
	//遷移パラメーターの作成   状態遷移時に使用する名前
	CrateTransitionParameter({
		{"Idle",        ExecutionState::TRIIGER}
		,{"Move",      ExecutionState::FLOAT}
		,{"GetReady",   ExecutionState::TRIIGER}
		,{"Throw",      ExecutionState::TRIIGER}
		});

	//基準値スピード
	float speed = 2.0f;

	//状態遷移フローの作成　　　　　　アニメーション名　　　　　遷移名　　　遷移名に重複がないように
	CreateAnyStateToTriggerTransition("PlayerIdle",           "Idle");
	CreateAnyStateToTriggerTransition("PlayerGetReady",       "GetReady");
	CreateAnyStateToTriggerTransition("PlayerThrow",	      "Throw");
	//                    //遷移元　　　遷移先　　　　遷移名 基準値　　状態　大きいか　小さいか
	CreateFloatTransition("PlayerIdle", "PlayerMove", "Move",speed, FloatState::Greater);

	
	//通知を受け取るコンポーネントの追加
	auto ob = player->AddComponent<ObserverComponent<SceneMessageType>>(player);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
		SceneMessageType::PLAYER_IDLE_STATE
		,SceneMessageType::PLAYER_BOOMERANG_GET_READY_STATE
		,SceneMessageType::PLAYER_BOOMERANG_ATTACK_STATE 
		}
		, std::bind(&PlayerAnimationController::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerAnimationController::~PlayerAnimationController()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void PlayerAnimationController::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);
	switch (type)
	{
		case SceneMessageType::PLAYER_IDLE_STATE:
			Play("PlayerIdle");
			break;
		case SceneMessageType::PLAYER_BOOMERANG_GET_READY_STATE:
			Play("PlayerGetReady");
			break;
		case SceneMessageType::PLAYER_BOOMERANG_ATTACK_STATE:
			SetTrigger("Throw");
			break;
		default:
			break;
	}


}
