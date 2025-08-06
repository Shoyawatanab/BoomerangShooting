/*
	クラス名     : RetryButton
	説明         : ゲームオーバーUIのリトライボタン
	補足・注意点 :
*/
#include "pch.h"
#include "RetryButton.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
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


	//シーン切り替え
	GetScene()->ChangeScene(SceneManager::SceneID::PLAY);
	//フェード開始
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
