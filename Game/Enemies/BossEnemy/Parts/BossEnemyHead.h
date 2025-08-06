/*
	クラス名     : BossEnemyHead
	説明         : ボス敵の頭モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyHead : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "Head";

public:
	//コンストラクタ
	BossEnemyHead(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyHead() override;

};