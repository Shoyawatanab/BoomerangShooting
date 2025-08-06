/*
	クラス名     : BossEnemyModel
	説明         : ボス敵のモデル
	補足・注意点 : 
*/
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