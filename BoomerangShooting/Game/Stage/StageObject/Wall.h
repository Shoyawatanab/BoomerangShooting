#pragma once
/*
	@file	Wall.h.h
	@brief	プレイシーンクラス
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
