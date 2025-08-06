/*
	クラス名     : LeftArrowButton
	説明         : セレクトシーンのステージUIの左矢印UI
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Button.h"

class Canvas;
class Button;

class LeftArrowButton : public Button
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{170.0f, 250.0f, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.2f, 0.2f, 0};
	//回転
	static constexpr float ROTATE {90.0f};
	//拡大率
	static constexpr float MAGNIFICATION { 1.2f };

public:
	//コンストラク
	LeftArrowButton(Canvas* canvas);
	//デストラクタ
	~LeftArrowButton() override;

private:
	//クリック時
	void OnClick();

	//範囲内になった時
	void InRange();
	//範囲外になった時
	void OutOfRange();


};

