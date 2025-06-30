#include "pch.h"
#include "ResultRetryButton.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
ResultRetryButton::ResultRetryButton(Canvas* canvas)
	:
	Button(canvas, "ResultRetry")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);


	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&ResultRetryButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&ResultRetryButton::InRange, this));
	comp->SetOutOfRangeFunction(std::bind(&ResultRetryButton::OutOfRange, this));

}

/// <summary>
/// デストラクタ
/// </summary>
ResultRetryButton::~ResultRetryButton()
{
}

/// <summary>
/// クリック時
/// </summary>
void ResultRetryButton::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);
	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// 範囲内になった時
/// </summary>
void ResultRetryButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void ResultRetryButton::OutOfRange()
{

	GetTransform()->SetScale(SCALE);


}
