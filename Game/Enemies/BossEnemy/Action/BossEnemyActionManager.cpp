/*
	クラス名     : BossEnemyActionManager
	説明         : ボス敵の行動のマネージャー
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyActionManager.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActions.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
BossEnemyActionManager::BossEnemyActionManager(BossEnemy* ower,Player* target, BossEnemyBeam* beam)
	:
	m_bossEnemy{ower}
{

	//各アクションの作成
	AddAction("Idle",std::make_unique<IdleingActionComtroller>());
	AddAction("JumpAttack",std::make_unique<BossJumpAttackActionController>(ower,target));
	AddAction("Walk",std::make_unique<WalkActionComtroller>(ower,target));
	AddAction("SwingDown",std::make_unique<SwingDownAttackActionController>(ower));
	AddAction("Beam",std::make_unique<BossBeamAttackActionController>(ower,beam,target));
	AddAction("Orientation", std::make_unique<OrientationActionController>(ower, target));
	AddAction("Orientation", std::make_unique<OrientationActionController>(ower, target));
	AddAction("Death", std::make_unique<BossDeathActionController>(ower));
	//初期アクションのセット
	SetStartAction("Idle");
	


	//通知を受け取るコンポーネントの追加
	auto ob = m_bossEnemy->AddComponent<ObserverComponent<SceneMessageType>>(m_bossEnemy);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::BOSS_IDLE_STATE
			,SceneMessageType::BOSS_BEAM_ATTACK_STATE
			,SceneMessageType::BOSS_JUMP_ATTACK_STATE
			,SceneMessageType::BOSS_SWING_DOWN_STATE
			,SceneMessageType::BOSS_WAKING_STATE }
		, std::bind(&BossEnemyActionManager::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyActionManager::~BossEnemyActionManager()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BossEnemyActionManager::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::BOSS_IDLE_STATE:
			//実行アクションタイプの変更
			m_bossEnemy->SetCurrentActionType(BossEnemy::ActionType::IDEL);
			ChangeAction("Idle");
			break;
		case SceneMessageType::BOSS_BEAM_ATTACK_STATE:
			//実行アクションタイプの変更
			m_bossEnemy->SetCurrentActionType(BossEnemy::ActionType::BEAM_ATTACK);
			ChangeAction("Beam");
			break;
		case SceneMessageType::BOSS_JUMP_ATTACK_STATE:
			//実行アクションタイプの変更
			m_bossEnemy->SetCurrentActionType(BossEnemy::ActionType::JUMP_ATTACK);
			ChangeAction("JumpAttack");
			break;
		case SceneMessageType::BOSS_WAKING_STATE:
			//実行アクションタイプの変更
			m_bossEnemy->SetCurrentActionType(BossEnemy::ActionType::WALK);
			ChangeAction("Walk");
			break;
		case SceneMessageType::BOSS_SWING_DOWN_STATE:
			//実行アクションタイプの変更
			m_bossEnemy->SetCurrentActionType(BossEnemy::ActionType::SWINGDOWN);
			ChangeAction("SwingDown");
			break;

		default:
			break;
	}
}
