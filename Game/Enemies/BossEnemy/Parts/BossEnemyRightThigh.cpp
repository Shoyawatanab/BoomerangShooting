/*
	クラス名     : BossEnemyRightThigh
	説明         : ボス敵の右太ももモデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyRightThigh.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightThigh::BossEnemyRightThigh(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyThigh"
		, Params::BOSSENEMY_RIGHTTHIGH_HP
		, Params::BOSSENEMY_RIGHTTHIGH_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_RIGHTTHIGH_SPHERE_COLLIDER_SIZE
		, boss)
{


	//以下追加部位の作成
//RightLegの生成
	auto rightLeg = GetScene()->AddActor<BossEnemyRightLeg>(GetScene(), boss);
	rightLeg->SetParent(this);

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTTHIGH_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTTHIGH_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTTHIGH_ROTATION);



}

BossEnemyRightThigh::~BossEnemyRightThigh()
{
}
