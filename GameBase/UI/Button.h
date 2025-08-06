/*
	クラス名     : Button
	説明         : ボタンUIの基底クラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"


class Canvas;
class ImageComponent;
class ButtonComponent;


class Button : public Actor
{
public:
	//コンストラク
	Button(Canvas* canvas, const std::string& textureName);
	//デストラクタ
	~Button();

private:

	ImageComponent* m_imageComponent;

	ButtonComponent* m_buttonComponent;
};
