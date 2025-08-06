/*
	クラス名     : InformationBase
	説明         : セレクトシーンの右の情報のまとめクラス
	補足・注意点 :
*/
#include "pch.h"
#include "InformationBase.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"
#include "Game/UI/SelectScene/InfmationBase/BackGraund/InformationBackGraund.h"
#include "Game/UI/SelectScene/InfmationBase/Stage1/StageOneInformation.h"
#include "Game/UI/SelectScene/InfmationBase/Stage2/StageTwoInformation.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
InformationBase::InformationBase(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_selectStageNumber{1}
	,m_drawStageNumber{1}
	,m_stage{}
{

	using namespace DirectX::SimpleMath;


	//背景
	auto backGraund = GetScene()->AddActor<InformationBackGraund>(canvas);
	backGraund->GetTransform()->SetParent(GetTransform());

	//ステージ１の情報
	auto stage1 = GetScene()->AddActor<StageOneInformation>(canvas);
	stage1->GetTransform()->SetParent(GetTransform());
	stage1->SetActive(true);
	m_stage.push_back(stage1);

	//ステージ２の情報
	auto stage2 = GetScene()->AddActor<StageTwoInformation>(canvas);
	stage2->GetTransform()->SetParent(GetTransform());
	stage2->SetActive(false);
	m_stage.push_back(stage2);


	GetTransform()->SetPosition(POSITION);
	GetTransform()->SetScale(SCALE);

	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);

	ob->Rigister(
		{
			SceneMessageType::STAGE_UP
			,SceneMessageType::STAGE_DOWN
		}
		, std::bind(&InformationBase::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);

}

/// <summary>
/// デストラクタ
/// </summary>
InformationBase::~InformationBase()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void InformationBase::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::STAGE_UP:
			//
			m_selectStageNumber++;
			m_selectStageNumber = std::min(2, m_selectStageNumber);
			//UIの切り替え
			ChangeStageUI(m_selectStageNumber);

			break;
		case SceneMessageType::STAGE_DOWN:
			//
			m_selectStageNumber--;
			m_selectStageNumber = std::max(1, m_selectStageNumber);
			//UIの切り替え
			ChangeStageUI(m_selectStageNumber);
			break;
		default:
			break;
	}
}

/// <summary>
/// ステージ番号UIの切り替え
/// </summary>
/// <param name="stateNumber"></param>
void InformationBase::ChangeStageUI(int stageNumber)
{
	//同じならやらない
	if (m_drawStageNumber == stageNumber)
	{
		return;
	}

	m_stage[m_drawStageNumber-1]->SetActive(false);

	m_stage[stageNumber -1]->SetActive(true);

	m_drawStageNumber = stageNumber;

}

