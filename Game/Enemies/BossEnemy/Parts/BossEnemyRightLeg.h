/*
	クラス名     : BossEnemyRightArmJoint
	説明         : ボス敵の右足モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyRightLeg : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightLeg";

public:
	//コンストラクタ
	BossEnemyRightLeg(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyRightLeg() override;

};