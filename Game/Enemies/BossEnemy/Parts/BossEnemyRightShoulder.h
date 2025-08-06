/*
	クラス名     : BossEnemyRightShoulder
	説明         : ボス敵の右肩モデル
	補足・注意点 :
*/
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