/*
	クラス名     : TitleButton
	説明         : ゲームオーバーUI
	補足・注意点 :
*/
#include "pch.h"
#include "GameOverUI.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"

#include "Game/UI/PlayScene/GameOver/BackGraund/GameOverBackGraund.h"
#include "Game/UI/PlayScene/GameOver/RetryButton/RetryButton.h"
#include "Game/UI/PlayScene/GameOver/TitleButton/TitleButton.h"
#include "Game/Messenger/Messengers.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
GameOverUI::GameOverUI(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_backGraund{}
	,m_retryButton{}
	,m_titleButton{}
{

	m_backGraund = GetScene()->AddActor<GameOverBackGraund>(canvas);
	m_backGraund->GetTransform()->SetParent(GetTransform());
	m_backGraund->SetActive(false);

	m_retryButton = GetScene()->AddActor<RetryButton>(canvas);
	m_retryButton->GetTransform()->SetParent(GetTransform());
	m_retryButton->SetActive(false);

	m_titleButton = GetScene()->AddActor<TitleButton>(canvas);
	m_titleButton->GetTransform()->SetParent(GetTransform());
	m_titleButton->SetActive(false);

	m_backGraund->SetActor(
		{
			m_retryButton
			,m_titleButton
		}
	);

	//通知を受け取るコンポーネントの追加
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::GAME_OVER
		}
		, std::bind(&GameOverUI::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);


}

/// <summary>
/// デストラクタ
/// </summary>
GameOverUI::~GameOverUI()
{
}



/// <summary>
/// アクティブになった時に呼ばれる関数
/// </summary>
void GameOverUI::OnEnable()
{



}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void GameOverUI::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::GAME_OVER:
			if (!m_backGraund->GetActive())
			{
				m_backGraund->SetActive(true);

			}
			break;
		default:
			break;
	}

}
