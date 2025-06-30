#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyPelvis : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "Pelvis";

public:
	//コンストラクタ
	BossEnemyPelvis(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyPelvis() override;

};