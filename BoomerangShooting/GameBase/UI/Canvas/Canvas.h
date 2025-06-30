#pragma once
#include "GameBase/Actor.h"

class Canvas : public Actor
{
public:

	//コンストラクタ
	Canvas(Scene * scene);
	//デストラクタ
	~Canvas();

};




/*
Unityの画面上にUIの表示・３D空間上に表示などをストラテジーパターンで切り替えられうような設計の実装をする

*/