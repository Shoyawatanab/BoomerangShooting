/*
	クラス名     : StageBackGraund
	説明         : セレクトシーンのステージUIの背景
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;
class Button;

class StageBackGraund : public Image
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{350.0f, 250.0f, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.6f, 0.6f, 0};
	//拡大率
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//コンストラク
	StageBackGraund(Canvas* canvas);
	//デストラクタ
	~StageBackGraund() override;


};

