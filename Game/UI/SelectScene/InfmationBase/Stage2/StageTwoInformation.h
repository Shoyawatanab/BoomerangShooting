/*
	クラス名     : StageTwoInformation
	説明         : セレクトシーンの右の情報(ステージ2の)
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class Canvas;

class StageTwoInformation : public Actor
{
public:
	//コンストラク
	StageTwoInformation(Canvas* canvas);
	//デストラクタ
	~StageTwoInformation() override;



};

