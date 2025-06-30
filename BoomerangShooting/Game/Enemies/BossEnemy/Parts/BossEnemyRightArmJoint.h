#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyRightArmJoint : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightArmJoint";

public:
	//コンストラクタ
	BossEnemyRightArmJoint(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyRightArmJoint() override;

};