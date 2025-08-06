/*
	クラス名     : TitleButton
	説明         : ゲームオーバーUIのタイトルボタン
	補足・注意点 :
*/
#include "pch.h"
#include "TitleButton.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
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

	//シーン切り替え
	GetScene()->ChangeScene(SceneManager::SceneID::TITLE);
	//フェードの開始
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


