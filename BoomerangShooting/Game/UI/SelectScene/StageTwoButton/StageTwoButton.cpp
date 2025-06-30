#include "pch.h"
#include "StageTwoButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
StageTwoButton::StageTwoButton(Canvas* canvas)
	:
	Button(canvas, "Stage1")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&StageTwoButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&StageTwoButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&StageTwoButton::OutOfRange,this));

}

/// <summary>
/// デストラクタ
/// </summary>
StageTwoButton::~StageTwoButton()
{
}

/// <summary>
/// クリック時
/// </summary>
void StageTwoButton::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);

	FadeManager::GetInstance()->StartFadeIn();
	//選択ステージ番号のセット
	GlobalGameData::GetInstance()->SetSelectStateNumber(2);

}

/// <summary>
/// 範囲内になった時
/// </summary>
void StageTwoButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void StageTwoButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
