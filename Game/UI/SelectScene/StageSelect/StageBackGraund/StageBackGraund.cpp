/*
	クラス名     : StageBackGraund
	説明         : セレクトシーンのステージUIの背景
	補足・注意点 :
*/
#include "pch.h"
#include "StageBackGraund.h"
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
StageBackGraund::StageBackGraund(Canvas* canvas)
	:
	Image(canvas, "StageBackGraund")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);




}

/// <summary>
/// デストラクタ
/// </summary>
StageBackGraund::~StageBackGraund()
{
}

