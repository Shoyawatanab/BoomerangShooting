/*
	クラス名     : BirdEnemyLeftFeather
	説明         : 鳥敵の左羽
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BirdEnemy/BirdEnemyParts.h"

class BirdEnemyLeftFeather : public BirdEnemyPars
{

public:

	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftFeaather";

public:
	//コンストラク
	BirdEnemyLeftFeather(Scene* scene);
	//デストラクタ
	~BirdEnemyLeftFeather() override;


};



