#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class ResultSceneBackGraund : public Image
{
public:
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 0.65f,0.65f,0.4f };
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 760,360,0 };

public:
	//コンストラク
	ResultSceneBackGraund(Canvas* canvas);
	//デストラクタ
	~ResultSceneBackGraund() override;


};