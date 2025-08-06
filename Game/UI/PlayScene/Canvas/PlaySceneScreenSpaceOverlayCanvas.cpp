/*
	クラス名     : PlaySceneScreenSpaceOverlayCanvas
	説明         : プレイシーンの常に画面に移るUIキャンバス
	補足・注意点 :
*/
#include "pch.h"
#include "PlaySceneScreenSpaceOverlayCanvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/PlayScene/PlaySceneUIs.h"
#include "Game/GlobalGameData.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
PlaySceneScreenSpaceOverlayCanvas::PlaySceneScreenSpaceOverlayCanvas(Scene* scene, std::vector<Actor*> targets)
	:
	ScreenSpaceOverlayCanvas(scene)
	,m_targetMarker{}
{

	//プレイシーンにきょうつうのUI

	//PlyerHpの作成
	GetScene()->AddActor<PlayerHp>(this);
	//ターゲットマーカー
	m_targetMarker = GetScene()->AddActor<TargetMarker>(this,targets);
	//ブーメランのカウント
	GetScene()->AddActor<BoomerangCount>(this);
	//ダメージUI
	GetScene()->AddActor<DamageCountFactory>(this);
	//プレイヤのダメージエフェクト
	GetScene()->AddActor<PlayerDamageEffect>(this);

	GetScene()->AddActor<BoomerangThrowUI>(this);

	//回収UI
	m_pickUpUI =  GetScene()->AddActor<PickUpUI>(this);


	//ステージごとのUI
	StageUI();


	//ゲームオーバーUI
	GetScene()->AddActor<GameOverUI>(this);

	//通知を受け取るコンポーネントの追加
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::PLAYER_PICKUP_POSSIBLE
			,SceneMessageType::PLAYER_PICKUP_IMPOSSIBLE
		}
		, std::bind(&PlaySceneScreenSpaceOverlayCanvas::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);


}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneScreenSpaceOverlayCanvas::~PlaySceneScreenSpaceOverlayCanvas()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void PlaySceneScreenSpaceOverlayCanvas::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::PLAYER_PICKUP_POSSIBLE:
			m_pickUpUI->SetActive(true);
			break;
		case SceneMessageType::PLAYER_PICKUP_IMPOSSIBLE:
			m_pickUpUI->SetActive(false);
			break;
		default:
			break;
	}

}

/// <summary>
/// ステージごとのUI
/// </summary>
void PlaySceneScreenSpaceOverlayCanvas::StageUI()
{
	//ステージ番号の取得
	int StageNumber = GlobalGameData::GetInstance()->GetSelectStateNumber();

	switch (StageNumber)
	{
		case 1:
			break;
		case 2:
			GetScene()->AddActor<BossHp>(this);

			break;
		default:
			break;
	}


}



