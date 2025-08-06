/*
	クラス名     : BossEnemyLeftArmJoint
	説明         : ボス敵の左腕関節モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyLeftArmJoint.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyLeftArmJoint::BossEnemyLeftArmJoint(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyArmJoint"
		, Params::BOSSENEMY_LEFTARMJOINT_HP
		, Params::BOSSENEMY_LEFTARMJOINT_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTARMJOINT_SPHERE_COLLIDER_SIZE
		, boss)
{


	//以下追加部位の作成

	auto leftArm = GetScene()->AddActor<BossEnemyLeftArm>(GetScene(), boss);
	leftArm->SetParent(this);


	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARMJOINT_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARMJOINT_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARMJOINT_ROTATION);
}

BossEnemyLeftArmJoint::~BossEnemyLeftArmJoint()
{
}
