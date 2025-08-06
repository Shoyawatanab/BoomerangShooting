#pragma once
/*
	@file	Floor.h.h
	@brief	プレイシーンクラス
*/
#pragma once
/*
	クラス名     : Floor
	説明         : 床
	補足・注意点 :
*/
#include "GameBase/Actor.h"
#include "Game/Stage/StageFactory.h"

class Floor : public Actor
{
public:

	//当たり判定の大きさ
	static constexpr DirectX::SimpleMath::Vector3 BOX_COLLIDER_SIZE = {1.0f,1.0f,1.0f};
	static constexpr float SPHERE_COLLIDER_SIZE = 2.0f;

public:
	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::STAGE; }


public:
	//コンストラクタ
	Floor(Scene* scene, StageFactory::StageParameter parameter );

	//デストラクタ
	~Floor() override;



};
