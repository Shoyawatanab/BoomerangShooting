/*
	クラス名     : BossEnemyLeftShoulder
	説明         : ボス敵の左肩モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyLeftShoulder : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftShoulder";

public:
	//コンストラクタ
	BossEnemyLeftShoulder(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyLeftShoulder() override;

	//部位破壊時の処理
	void PartsDestruction() override;


};