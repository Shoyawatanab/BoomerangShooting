#pragma once
#include "Game/Enemies/BirdEnemy/BirdEnemyParts.h"

class BirdEnemyRightFeather : public BirdEnemyPars
{

public:

	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightFeaather";

public:
	//コンストラク
	BirdEnemyRightFeather(Scene* scene);
	//デストラクタ
	~BirdEnemyRightFeather() override;


};