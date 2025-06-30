#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyLeftArmJoint : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftArmJoint";

public:
	//コンストラクタ
	BossEnemyLeftArmJoint(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyLeftArmJoint() override;

};