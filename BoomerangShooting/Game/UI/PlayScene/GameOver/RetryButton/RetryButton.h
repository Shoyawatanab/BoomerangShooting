#pragma once
#include "GameBase/UI/Button.h"

class Canvas;

class RetryButton : public Button
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{480, 450, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.5f, 0.5f, 0};
	//拡大率
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//コンストラク
	RetryButton(Canvas* canvas);
	//デストラクタ
	~RetryButton();

private:
	//クリック時
	void OnClick();

	//範囲内になった時
	void InRange();
	//範囲外になった時
	void OutOfRange();


};
