/*
	クラス名     : TimeSeparator
	説明         : リザルトシーンの時間UIの分と秒の間の点のUI
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class TimeSeparator : public Image
{

	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 1.0f,1.0f,1.0f };

public:
	//コンストラク
	TimeSeparator(Canvas* canvas);
	//デストラクタ
	~TimeSeparator() override;


};
