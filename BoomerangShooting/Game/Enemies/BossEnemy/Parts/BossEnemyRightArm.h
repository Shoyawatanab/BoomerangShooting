#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyRightArm : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightArm";

public:
	//コンストラクタ
	BossEnemyRightArm(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyRightArm() override;


	//個別の当たった時の関数
	void OnCollisionEnterActor(ColliderComponent* collider);


};