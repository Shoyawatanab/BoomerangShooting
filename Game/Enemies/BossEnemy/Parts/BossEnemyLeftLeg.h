/*
	クラス名     : BossEnemyLeftLeg
	説明         : ボス敵の左足モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyLeftLeg : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftLeg";

public:
	//コンストラクタ
	BossEnemyLeftLeg(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyLeftLeg() override;

};