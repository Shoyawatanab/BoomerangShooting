#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyBottom : public BossEnemyParts
{
public:
	//パーツ名
	static constexpr const char PARTS_NAME[] = "Bottom";

public:
	//コンストラクタ
	BossEnemyBottom(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyBottom() override;

};