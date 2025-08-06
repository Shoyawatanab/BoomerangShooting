/*
	クラス名     : InformationBackGraund
	説明         : セレクトシーンの右の情報の背景
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;
class Button;

class InformationBackGraund : public Image
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{0.0f, 0.0f, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.9f, 0.9f, 0};
	//拡大率
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//コンストラク
	InformationBackGraund(Canvas* canvas);
	//デストラクタ
	~InformationBackGraund() override;


};

