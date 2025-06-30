#pragma once
#include "GameBase/UI/Button.h"

class Canvas;

class ResultRetryButton : public Button
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{590, 500, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{1.0f, 1.0f, 0};
	//拡大率
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//コンストラク
	ResultRetryButton(Canvas* canvas);
	//デストラクタ
	~ResultRetryButton();

private:
	//クリック時
	void OnClick();

	//範囲内になった時
	void InRange();
	//範囲外になった時
	void OutOfRange();


};
