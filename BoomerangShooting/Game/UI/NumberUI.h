#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Image;

class NumberUI : public Actor
{
public:
	//１桁の横幅
	static constexpr float DIGITWIDTH{0.1f}
	;
public:
	//コンストラクタ
	NumberUI(Canvas* canvas);
	//デストラクタ
	~NumberUI() override;
	//数字の登録
	void SetNumber(int number);

private:

	//番号イメージ
	Image* m_number;

};

