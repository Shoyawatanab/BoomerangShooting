#pragma once
/*
	@file	Floor.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Stage/StageFactory.h"

class Floor : public Actor
{
public:
	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::STAGE; }


public:
	//コンストラクタ
	Floor(Scene* scene, StageFactory::StageParameter parameter );

	//デストラクタ
	~Floor() override;



};
