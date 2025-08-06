/*
	クラス名     : DecisionButton
	説明         : セレクトシーンの決定のボタン
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Button.h"

class Canvas;
class Button;

class DecisionButton : public Button
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{350.0f, 500.0f, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.3f, 0.3f, 0};
	//拡大率
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//コンストラク
	DecisionButton(Canvas* canvas);
	//デストラクタ
	~DecisionButton() override;

private:
	//クリック時
	void OnClick();

	//範囲内になった時
	void InRange();
	//範囲外になった時
	void OutOfRange();


};

