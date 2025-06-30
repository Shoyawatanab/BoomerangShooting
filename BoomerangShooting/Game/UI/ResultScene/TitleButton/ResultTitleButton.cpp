#include "pch.h"
#include "ResultTitleButton.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
ResultTitleButton::ResultTitleButton(Canvas* canvas)
	:
	Button(canvas, "ResultTitle")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);



	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&ResultTitleButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&ResultTitleButton::InRange, this));
	comp->SetOutOfRangeFunction(std::bind(&ResultTitleButton::OutOfRange, this));

}

/// <summary>
/// デストラクタ
/// </summary>
ResultTitleButton::~ResultTitleButton()
{
}



/// <summary>
/// クリック時
/// </summary>
void ResultTitleButton::OnClick()
{
	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_TITLE_SCENE);
	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// 範囲内になった時
/// </summary>
void ResultTitleButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void ResultTitleButton::OutOfRange()
{

	GetTransform()->SetScale(SCALE);


}


