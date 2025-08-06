/*
	クラス名     : TitleSceneScreenSpaceOverlayCanvas
	説明         : タイトルシーンの常に映り続けるUIキャンバス
	補足・注意点 :
*/
#include "pch.h"
#include "TitleSceneScreenSpaceOverlayCanvas.h"
#include "Game/UI/TitleScene/TitleSceneUIs.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
TitleSceneScreenSpaceOverlayCanvas::TitleSceneScreenSpaceOverlayCanvas(Scene* scene)
	:
	ScreenSpaceOverlayCanvas(scene)
{
	using namespace DirectX::SimpleMath;

	auto logo =GetScene()->AddActor<Image>(this,"Logo");
	logo->GetTransform()->SetPosition(LOGO_POSITION);
	logo->GetTransform()->SetScale(LOGO_SCALE);

	//
	GetScene()->AddActor<ExitButton>(this);
	GetScene()->AddActor<PlayButton>(this);

}

/// <summary>
/// デストラクタ
/// </summary>
TitleSceneScreenSpaceOverlayCanvas::~TitleSceneScreenSpaceOverlayCanvas()
{
}
