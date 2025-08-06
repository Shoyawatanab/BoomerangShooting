/*
	クラス名     : BossEnemyLeftShoulder
	説明         : ボス敵の左太ももモデル
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyLeftThigh : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftThigh";

public:
	//コンストラクタ
	BossEnemyLeftThigh(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyLeftThigh() override;

};