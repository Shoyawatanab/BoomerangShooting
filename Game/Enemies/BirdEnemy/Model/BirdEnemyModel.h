/*
	クラス名     : BirdEnemyModel
	説明         : 鳥敵のモデル
	補足・注意点 :
*/
#pragma once
#include "GameBase/Model/ModelBase.h"


class BirdEnemyModel : public ModelBase
{
public:
	//コンストラク
	BirdEnemyModel(Scene* scene);
	//デストラクタ
	~BirdEnemyModel() override;


};

