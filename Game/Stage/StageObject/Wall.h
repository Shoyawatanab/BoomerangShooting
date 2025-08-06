/*
	クラス名     : Wall
	説明         : 壁
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Stage/StageFactory.h"



class Wall : public Actor
{
public:
	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::STAGE; }

public:
	//コンストラクタ
	Wall(Scene* scene, StageFactory::StageParameter parameter);

	//デストラクタ
	~Wall() override;


};
