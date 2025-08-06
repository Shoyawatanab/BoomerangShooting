/*
	クラス名     : LeftArrowButton
	説明         : セレクトシーンのステージUIの左矢印UI
	補足・注意点 :
*/
#include "pch.h"
#include "LeftArrowButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Messenger/Messengers.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
LeftArrowButton::LeftArrowButton(Canvas* canvas)
	:
	Button(canvas, "SelectSceneArow")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);


	auto image = GetComponent<ImageComponent>();
	image->SetAngle(DirectX::XMConvertToRadians(ROTATE));

	auto comp = GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&LeftArrowButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&LeftArrowButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&LeftArrowButton::OutOfRange,this));


}

/// <summary>
/// デストラクタ
/// </summary>
LeftArrowButton::~LeftArrowButton()
{
}

/// <summary>
/// クリック時
/// </summary>
void LeftArrowButton::OnClick()
{

	Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::STAGE_DOWN);

}

/// <summary>
/// 範囲内になった時
/// </summary>
void LeftArrowButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void LeftArrowButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
