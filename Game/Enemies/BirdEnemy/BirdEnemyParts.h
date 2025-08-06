/*
	クラス名     : BirdEnemyPars
	説明         : 鳥敵のパーツの基底クラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Model/ModelPartsBase.h"


class BirdEnemyPars : public  ModelPartsBase
{
public:

	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BOSS_ENEMY_PARTS; }

public:
	//コンストラク
	BirdEnemyPars(Scene* scene,const  std::string& partsName, const std::string& modelName);
	//デストラクタ
	~BirdEnemyPars() override;

};


