/*
	クラス名     : BossEnemyRightThigh
	説明         : ボス敵の右太ももモデル
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
class BossEnemy;


class BossEnemyRightThigh : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightThigh";

public:
	//コンストラクタ
	BossEnemyRightThigh(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyRightThigh() override;

};