#include "pch.h"
#include "PlayButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Messenger/Global/GlobalMessages.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
PlayButton::PlayButton(Canvas* canvas)
	:
	Button(canvas, "PLAY")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&PlayButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&PlayButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&PlayButton::OutOfRange,this));

}

/// <summary>
/// デストラクタ
/// </summary>
PlayButton::~PlayButton()
{
}

/// <summary>
/// クリック時
/// </summary>
void PlayButton::OnClick()
{
	
	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_SELECT_SCENE);

	FadeManager::GetInstance()->StartFadeIn();

}

/// <summary>
/// 範囲内になった時
/// </summary>
void PlayButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void PlayButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
