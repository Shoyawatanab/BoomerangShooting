#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
class BossEnemy;


class BossEnemyRightShoulder : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightShoulder";

public:
	//コンストラクタ
	BossEnemyRightShoulder(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyRightShoulder() override;

};