/*
	クラス名     : RightArrowButton
	説明         : セレクトシーンのステージUIの右矢印UI
	補足・注意点 :
*/
#include "pch.h"
#include "RightArrowButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"


#include "Game/Messenger/Messengers.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
RightArrowButton::RightArrowButton(Canvas* canvas)
	:
	Button(canvas, "SelectSceneArow")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto image = GetComponent<ImageComponent>();
	image->SetAngle(DirectX::XMConvertToRadians(ROTATE));


	auto comp = GetComponent<ButtonComponent>();

	comp->SetClickFunction(std::bind(&RightArrowButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&RightArrowButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&RightArrowButton::OutOfRange,this));




}

/// <summary>
/// デストラクタ
/// </summary>
RightArrowButton::~RightArrowButton()
{
}

/// <summary>
/// クリック時
/// </summary>
void RightArrowButton::OnClick()
{

	Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::STAGE_UP);
}

/// <summary>
/// 範囲内になった時
/// </summary>
void RightArrowButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void RightArrowButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
