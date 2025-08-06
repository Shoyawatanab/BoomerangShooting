/*
	クラス名     : StageOneImage
	説明         : セレクトシーンのステージ１の画像
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;
class Button;

class StageOneImage : public Image
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{350.0f, 250.0f, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.4f, 0.4f, 0};

public:
	//コンストラク
	StageOneImage(Canvas* canvas);
	//デストラクタ
	~StageOneImage() override;


};

