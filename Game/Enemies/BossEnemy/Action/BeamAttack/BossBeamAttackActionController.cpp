/*
	クラス名     : BossBeamAttackActionController
	説明         : ボス敵のビーム攻撃のコントローラー
	補足・注意点 :
*/
#include "pch.h"
#include "BossBeamAttackActionController.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossBeamAttackActionController::BossBeamAttackActionController(BossEnemy* bossenemy
	, BossEnemyBeam* beam
	, Actor* player)
	:
	m_commonResources{}
	,m_preliminaryAction{}
	,m_charge{}
	,m_shot{}
	,m_attackEnd{}
	,m_beam{beam}
{
	//各状態の生成
	m_preliminaryAction = std::make_unique<BossBeamAttackPreliminaryAction>(bossenemy,beam,this);
	m_charge = std::make_unique<BossBeamAttackCharge>( bossenemy, beam,this);
	m_shot = std::make_unique<BossBeamAttackShot>( bossenemy, beam,this,player);
	m_attackEnd = std::make_unique<BossBeamAttackEnd>( bossenemy, beam,this);



	//行動順に追加
	AddAction(
		{
		m_preliminaryAction.get()
		,m_charge.get()
		,m_shot.get()
		,m_attackEnd.get()
		}
	);


	//通知を受け取るコンポーネントの追加
	auto ob = bossenemy->AddComponent<ObserverComponent<SceneMessageType>>(bossenemy);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::BOSS_BEAM_IMPACT
		}
		, std::bind(&BossBeamAttackActionController::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackActionController::~BossBeamAttackActionController()
{
}

/// <summary>
/// 通知時に呼び出す関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BossBeamAttackActionController::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);
	switch (type)
	{
		case SceneMessageType::BOSS_BEAM_IMPACT:
			//ステートをShotからEndに変更
			ChangeState();
			break;
		default:
			break;
	}

}

/// <summary>
/// 行動の中止
/// </summary>
void BossBeamAttackActionController::ActionCancel()
{

	m_beam->SetActive(false);
}





