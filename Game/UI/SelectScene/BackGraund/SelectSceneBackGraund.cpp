/*
	クラス名     : SelectSceneBackGraund
	説明         : セレクトシーンの背景UII
	補足・注意点 :
*/
#include "pch.h"
#include "SelectSceneBackGraund.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
SelectSceneBackGraund::SelectSceneBackGraund(Canvas* canvas)
	:
	Image(canvas, "BackGraund")
{

	//auto image = GetScene()->AddActor<Image>(canvas,"BackGraund");
	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITION);

}

SelectSceneBackGraund::~SelectSceneBackGraund()
{
}
