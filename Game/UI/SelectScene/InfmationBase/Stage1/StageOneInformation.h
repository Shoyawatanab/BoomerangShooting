/*
	クラス名     : StageOneInformation
	説明         : セレクトシーンの右の情報(ステージ１の)
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class Canvas;

class StageOneInformation : public Actor
{
public:

	static constexpr DirectX::SimpleMath::Vector3 BIRD_ONE_POSITION = { -100, 0, 0 };
	static constexpr DirectX::SimpleMath::Vector3 BIRD_TWO_POSITION = {100, 0, 0 };

public:
	//コンストラク
	StageOneInformation(Canvas* canvas);
	//デストラクタ
	~StageOneInformation() override;


};

