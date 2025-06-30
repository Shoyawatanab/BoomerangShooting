#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyLeftShoulder : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftShoulder";

public:
	//コンストラクタ
	BossEnemyLeftShoulder(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyLeftShoulder() override;

};