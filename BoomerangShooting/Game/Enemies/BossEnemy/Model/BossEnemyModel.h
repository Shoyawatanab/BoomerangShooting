#pragma once
#include "GameBase/Model/ModelBase.h"

class BossEnemy;

class BossEnemyModel : public ModelBase
{
public:
	//コンストラクタ
	BossEnemyModel(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyModel() override;
	

};