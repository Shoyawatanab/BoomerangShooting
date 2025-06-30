#include "pch.h"
#include "StageOneButton.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
StageOneButton::StageOneButton(Canvas* canvas)
	:
	Button(canvas, "Tutorial")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

	auto comp = GetComponent<ButtonComponent>();


	comp->SetClickFunction(std::bind(&StageOneButton::OnClick, this));
	comp->SetInRangeFunction(std::bind(&StageOneButton::InRange,this));
	comp->SetOutOfRangeFunction(std::bind(&StageOneButton::OutOfRange,this));

}

/// <summary>
/// デストラクタ
/// </summary>
StageOneButton::~StageOneButton()
{
}

/// <summary>
/// クリック時
/// </summary>
void StageOneButton::OnClick()
{

	GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_PLAY_SCENE);

	FadeManager::GetInstance()->StartFadeIn();
	//選択ステージ番号のセット
	GlobalGameData::GetInstance()->SetSelectStateNumber(1);

}

/// <summary>
/// 範囲内になった時
/// </summary>
void StageOneButton::InRange()
{
	GetTransform()->SetScale(SCALE * MAGNIFICATION);

}

/// <summary>
/// 範囲外になった時
/// </summary>
void StageOneButton::OutOfRange()
{
	GetTransform()->SetScale(SCALE);

}
