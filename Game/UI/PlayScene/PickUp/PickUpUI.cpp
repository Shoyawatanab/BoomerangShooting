/*
	クラス名     : PickUpUI
	説明         : 回収可能UI
	補足・注意点 :
*/
#include "pch.h"
#include "PickUpUI.h"
#include "Game/Component/Components.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
PickUpUI::PickUpUI(Canvas* canvas)
	:
	Image(canvas,"F")
{
	
	GetTransform()->SetPosition(POSITION);
	GetTransform()->SetScale(SCALE);


	SetActive(false);
}

/// <summary>
/// デストラクタ
/// </summary>
PickUpUI::~PickUpUI()
{
}
