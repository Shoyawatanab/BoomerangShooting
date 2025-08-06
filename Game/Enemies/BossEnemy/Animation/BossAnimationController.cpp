/*
	クラス名     : BossAnimationController
	説明         : ボス敵のアニメーションコントローラー
	補足・注意点 :
*/
#include "pch.h"
#include "BossAnimationController.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Enemies/BossEnemy/Model/BossEnemyModel.h"
#include "Game/Messenger/Messengers.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player"></param>
BossAnimationController::BossAnimationController(BossEnemy* bossEnemy)
	:
	AnimationController()
{

	//パーツ情報の取得
	auto partss = bossEnemy->GetModel()->GetParts();


	//名前とトランスフォームのペアの作成
	//格納変数
	std::vector<std::pair<std::string,Actor*>> data;

	for (auto& parts : partss)
	{
		//名前とトランスフォームの追加
		data.push_back(std::make_pair(parts.first,parts.second));
	}
	
	

	//各Animationの作成
	AddAnimatoin(bossEnemy,"BossIdle","Resources/Json/BossEnemyData/Animation/Idle.json",data,true);
	AddAnimatoin(bossEnemy,"BossMove","Resources/Json/BossEnemyData/Animation/Move.json",data);
	AddAnimatoin(bossEnemy,"BossSwingDown","Resources/Json/BossEnemyData/Animation/SwingDown.json",data);
	AddAnimatoin(bossEnemy,"BossJumpCharge","Resources/Json/BossEnemyData/Animation/JumpCharge.json",data);
	AddAnimatoin(bossEnemy,"BossFallDown","Resources/Json/BossEnemyData/Animation/FallDown.json",data);
	AddAnimatoin(bossEnemy,"BeamAttack","Resources/Json/BossEnemyData/Animation/BeamAttack.json",data);
	AddAnimatoin(bossEnemy,"BeamAttackEnd","Resources/Json/BossEnemyData/Animation/BeamAttackEnd.json",data);
	


	//遷移パラメーターの作成   状態遷移時に使用する名前
	CrateTransitionParameter({
		{"Move",             ExecutionState::FLOAT}
		,{"SwingDown",       ExecutionState::TRIIGER}
		,{"JumpCharge",      ExecutionState::TRIIGER}
		,{"BeamEnd",      ExecutionState::TRIIGER}
		});

	//基準値スピード
	float speed = 0.01f;

	//状態遷移フローの作成　　　　　　アニメーション名　　　　　遷移名　　　遷移名に重複がないように
	CreateAnyStateToTriggerTransition("BossIdle",           "Idle");
	CreateAnyStateToTriggerTransition("BossSwingDown",       "SwingDown");
	CreateAnyStateToTriggerTransition("BossJumpCharge",	      "JumpCharge");

	CreateTriggerTransition("BeamAttack", "BeamAttackEnd", "BeamEnd");



	//                    //遷移元　　　遷移先　　　　遷移名 基準値　　状態　大きいか　小さいか
	CreateFloatTransition("BossIdle", "BossMove", "Move",speed, FloatState::Greater);

	//通知を受け取るコンポーネントの追加
	auto ob = bossEnemy->AddComponent<ObserverComponent<SceneMessageType>>(bossEnemy);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::BOSS_IDLE_STATE
			,SceneMessageType::BOSS_BEAM_ATTACK_STATE
			,SceneMessageType::BOSS_JUMP_ANIMATION_START
			,SceneMessageType::BOSS_SWING_DOWN_STATE
			,SceneMessageType::BOSS_WAKING_STATE
			,SceneMessageType::BOSS_DEFEATED
			,SceneMessageType::BOSS_BEAM_IMPACT
		}
		, std::bind(&BossAnimationController::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);

}

/// <summary>
/// デストラクタ
/// </summary>
BossAnimationController::~BossAnimationController()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BossAnimationController::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::BOSS_IDLE_STATE:
			Play("BossIdle");
			break;
		case SceneMessageType::BOSS_BEAM_ATTACK_STATE:
			Play("BeamAttack");
			break;
		case SceneMessageType::BOSS_JUMP_ANIMATION_START:
			SetTrigger("JumpCharge");
			break;
		case SceneMessageType::BOSS_WAKING_STATE:
			SetTrigger("Move");
			break;
		case SceneMessageType::BOSS_SWING_DOWN_STATE:
			SetTrigger("SwingDown");
			break;
		case SceneMessageType::BOSS_DEFEATED:  // ボスを倒したとき
			Play("BossFallDown");
			break;
		case SceneMessageType::BOSS_BEAM_IMPACT:
			SetTrigger("BeamEnd");
			break;
		default:
			break;
	}


}
