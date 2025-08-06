/*
	クラス名     : PickUpUI
	説明         : 回収可能UI
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class PickUpUI : public Image
{
public:

	static constexpr DirectX::SimpleMath::Vector3 POSITION{640, 360, 0};
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.2f, 0.2f, 0};


public:
	//コンストラク
	PickUpUI(Canvas* canvas);
	//デストラクタ
	~PickUpUI();


};