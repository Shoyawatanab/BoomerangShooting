/*
	クラス名     : BirdEnemyBody
	説明         : 鳥敵の体
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BirdEnemy/BirdEnemyParts.h"


class BirdEnemyBody : public BirdEnemyPars
{
public:

	//パーツ名
	static constexpr const char PARTS_NAME[] = "Body";

public:
	//コンストラク
	BirdEnemyBody(Scene* scene);
	//デストラクタ
	~BirdEnemyBody() override;


};



