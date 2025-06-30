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
