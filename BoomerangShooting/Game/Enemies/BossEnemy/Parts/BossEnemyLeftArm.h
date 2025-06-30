#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyLeftArm : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftArm";

public:
	//コンストラクタ
	BossEnemyLeftArm(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyLeftArm() override;

	//個別の当たった時の関数
	void OnCollisionEnterActor(ColliderComponent* collider);



};