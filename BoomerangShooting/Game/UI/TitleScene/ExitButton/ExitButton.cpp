#include "pch.h"
#include "ExitButton.h"
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
ExitButton::ExitButton(Canvas* canvas)
	:
	Button(canvas, "EXIT")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&ExitButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&ExitButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&ExitButton::OutOfRange,this));

}

/// <summary>
/// デストラクタ
/// </summary>
ExitButton::~ExitButton()
{
}

/// <summary>
/// クリック時
/// </summary>
void ExitButton::OnClick()
{
	
	PostQuitMessage(0);

}

/// <summary>
/// 範囲内になった時
/// </summary>
void ExitButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void ExitButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
