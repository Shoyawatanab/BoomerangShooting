#pragma once
#include "GameBase/Component.h"


class ButtonComponent : public Component
{
public:
	//クリック時の関数の登録　
	void SetClickFunction(std::function<void()> function) { m_clickFunction = function; };
	//範囲に入った時関数
	void SetInRangeFunction(std::function<void()> function) { m_inRangeFunction = function; };
	//範囲外になった時関数
	void SetOutOfRangeFunction(std::function<void()> function) { m_outOfRangeFunction = function; };

public:
	//コンストラク
	ButtonComponent(Actor* owner);
	//デストラクタ
	~ButtonComponent();
	
	//クリック時
	void OnClick();
	//範囲内になった時の処理
	void InRange();
	//範囲外になった時の処理
	void OutOfRange();

private:
	//クリック時関数
	std::function<void()> m_clickFunction;

	//範囲に入った時関数
	std::function<void()> m_inRangeFunction;

	//範囲外になった時関数
	std::function<void()> m_outOfRangeFunction;

};