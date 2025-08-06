/*
	クラス名     : BossEnemyRightArmJoint
	説明         : ボス敵の右足モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyRightLeg.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"

BossEnemyRightLeg::BossEnemyRightLeg(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyLeg"
		, Params::BOSSENEMY_RIGHTLEG_HP
		, Params::BOSSENEMY_RIGHTLEG_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_RIGHTLEG_SPHERE_COLLIDER_SIZE
		, boss)
{


	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTLEG_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTLEG_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTLEG_ROTATION);

	//以下追加部位の作成


}

BossEnemyRightLeg::~BossEnemyRightLeg()
{
}
