#pragma once
#include "GameBase/UI/Button.h"

class Canvas;

class PlayButton : public Button
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{750, 600, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{1.0f, 1.0f, 0};
	//拡大率
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//コンストラク
	PlayButton(Canvas* canvas);
	//デストラクタ
	~PlayButton() override;

private:
	//クリック時
	void OnClick();

	//範囲内になった時
	void InRange();
	//範囲外になった時
	void OutOfRange();

};

