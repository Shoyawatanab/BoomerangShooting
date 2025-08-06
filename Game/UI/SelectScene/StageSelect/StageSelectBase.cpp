/*
	クラス名     : StageSelectBase
	説明         : セレクトシーンのステージUIのまとめクラス
	補足・注意点 :
*/
#include "pch.h"
#include "StageSelectBase.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/SelectScene/StageSelect/StageBackGraund/StageBackGraund.h"
#include "Game/UI/SelectScene/StageSelect/StageOneImage/StageOneImage.h"
#include "Game/UI/SelectScene/StageSelect/StageTwoImage/StageTwoImage.h"
#include "Game/UI/SelectScene/StageSelect/ChangeStageArrow/LeftArrowButton.h"
#include "Game/UI/SelectScene/StageSelect/ChangeStageArrow/RightArrowButton.h"
#include "Game/GlobalGameData.h"
#include "Game/Messenger/Messengers.h"



/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
StageSelectBase::StageSelectBase(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_selectStageNumber{1}
	,m_drawStageNumber{1}
{
	using namespace DirectX::SimpleMath;


	//ステージの背景
	GetScene()->AddActor<StageBackGraund>(canvas);
	//ステージ画像
	auto one = GetScene()->AddActor<StageOneImage>(canvas);
	m_stageUI.push_back(one);

	auto two = GetScene()->AddActor<StageTwoImage>(canvas);
	two->SetActive(false);
	m_stageUI.push_back(two);


	//ステージ切り替えボタン
	GetScene()->AddActor<LeftArrowButton>(canvas);
	GetScene()->AddActor<RightArrowButton>(canvas);

	//通知コンポーネント
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//登録
	ob->Rigister(
		{
			SceneMessageType::STAGE_UP
			,SceneMessageType::STAGE_DOWN
		}
		,std::bind(&StageSelectBase::Notify,this,std::placeholders::_1,std::placeholders::_2)
	);



}

/// <summary>
/// デストラクタ
/// </summary>
StageSelectBase::~StageSelectBase()
{



}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void StageSelectBase::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::STAGE_UP:
			//
			m_selectStageNumber++;
			m_selectStageNumber = std::min(MAX_STAGE_COUNT, m_selectStageNumber);
			//UIの切り替え
			ChangeStageUI(m_selectStageNumber);
			break;
		case SceneMessageType::STAGE_DOWN:
			m_selectStageNumber--;
			m_selectStageNumber = std::max(1, m_selectStageNumber);
			//UIの切り替え
			ChangeStageUI(m_selectStageNumber);
			break;
		default:
			break;
	}

	GlobalGameData::GetInstance()->SetSelectStateNumber(m_selectStageNumber);
}

/// <summary>
/// ステージ番号UIの切り替え
/// </summary>
/// <param name="stateNumber"></param>
void StageSelectBase::ChangeStageUI(int stateNumber)
{
	//同じなら切り替えない
	if (m_drawStageNumber == stateNumber)
	{
		return;
	}

	//描画しているUIを非アクティブ化
	m_stageUI[m_drawStageNumber-1]->SetActive(false);

	//UIを非アクティブ化
	m_stageUI[stateNumber-1]->SetActive(true);

	//番号の切り替え
	m_drawStageNumber = stateNumber;

}
