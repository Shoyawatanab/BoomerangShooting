/*
	クラス名     : StageOneImage
	説明         : セレクトシーンのステージ１の画像
	補足・注意点 :
*/
#include "pch.h"
#include "StageOneImage.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
StageOneImage::StageOneImage(Canvas* canvas)
	:
	Image(canvas, "Stage1")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);




}

/// <summary>
/// デストラクタ
/// </summary>
StageOneImage::~StageOneImage()
{
}

