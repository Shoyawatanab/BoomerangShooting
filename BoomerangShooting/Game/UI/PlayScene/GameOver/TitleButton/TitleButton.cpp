#include "pch.h"
#include "TitleButton.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
TitleButton::TitleButton(Canvas* canvas)
	:
	Button(canvas, "ClearTitleTex")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);


	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&TitleButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&TitleButton::InRange, this));
	comp->SetOutOfRangeFunction(std::bind(&TitleButton::OutOfRange, this));

}

/// <summary>
/// デストラクタ
/// </summary>
TitleButton::~TitleButton()
{
}



/// <summary>
/// クリック時
/// </summary>
void TitleButton::OnClick()
{
	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_TITLE_SCENE);
	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// 範囲内になった時
/// </summary>
void TitleButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void TitleButton::OutOfRange()
{

	GetTransform()->SetScale(SCALE);


}


