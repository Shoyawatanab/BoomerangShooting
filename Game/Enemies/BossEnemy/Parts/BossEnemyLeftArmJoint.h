/*
	クラス名     : BossEnemyLeftArmJoint
	説明         : ボス敵の左腕関節モデル
	補足・注意点 :
*/
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