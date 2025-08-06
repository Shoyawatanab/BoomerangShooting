/*
	クラス名     : BossEnemyBottom
	説明         : ボス敵の尻モデル
	補足・注意点 :
*/
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