/*
	クラス名     : DecisionButton
	説明         : セレクトシーンの決定のボタン
	補足・注意点 :
*/
#include "pch.h"
#include "DecisionButton.h"
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
DecisionButton::DecisionButton(Canvas* canvas)
	:
	Button(canvas, "SelectPlay")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&DecisionButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&DecisionButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&DecisionButton::OutOfRange,this));


	//NormalGraund

}

/// <summary>
/// デストラクタ
/// </summary>
DecisionButton::~DecisionButton()
{
}

/// <summary>
/// クリック時
/// </summary>
void DecisionButton::OnClick()
{

	//GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);

	GetScene()->ChangeScene(SceneManager::SceneID::PLAY);

	FadeManager::GetInstance()->StartFadeIn();


}

/// <summary>
/// 範囲内になった時
/// </summary>
void DecisionButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void DecisionButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
