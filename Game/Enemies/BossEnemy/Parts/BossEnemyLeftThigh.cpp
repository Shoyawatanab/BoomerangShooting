/*
	クラス名     : BossEnemyLeftShoulder
	説明         : ボス敵の左太ももモデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyLeftThigh.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyLeftThigh::BossEnemyLeftThigh(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyThigh"
		, Params::BOSSENEMY_LEFTTHIGH_HP
		, Params::BOSSENEMY_LEFTTHIGH_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTTHIGH_SPHERE_COLLIDER_SIZE
		, boss)
{


	//以下追加部位の作成
	//LeftLegの生成
	auto leftLeg = GetScene()->AddActor<BossEnemyLeftLeg>(GetScene(), boss);
	leftLeg->SetParent(this);

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_LEFTTHIGH_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTTHIGH_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTTHIGH_ROTATION);

}

BossEnemyLeftThigh::~BossEnemyLeftThigh()
{
}
