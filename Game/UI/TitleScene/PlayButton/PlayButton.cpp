/*
	クラス名     : PlayButton
	説明         : タイトルシーンのPlayボタンのUI
	補足・注意点 :
*/
#include "pch.h"
#include "PlayButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"

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
	
	//シーン切り替え
	GetScene()->ChangeScene(SceneManager::SceneID::STAGESELECT);


	FadeManager::GetInstance()->StartFadeIn(FadeManager::FadeInKinds::BOMERANG_FADE_IN);

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
