#include "pch.h"
#include "RetryButton.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
RetryButton::RetryButton(Canvas* canvas)
	:
	Button(canvas, "ClearReTryTex")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);


	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&RetryButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&RetryButton::InRange, this));
	comp->SetOutOfRangeFunction(std::bind(&RetryButton::OutOfRange, this));

}

/// <summary>
/// デストラクタ
/// </summary>
RetryButton::~RetryButton()
{
}

/// <summary>
/// クリック時
/// </summary>
void RetryButton::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);
	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// 範囲内になった時
/// </summary>
void RetryButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void RetryButton::OutOfRange()
{

	GetTransform()->SetScale(SCALE);


}
