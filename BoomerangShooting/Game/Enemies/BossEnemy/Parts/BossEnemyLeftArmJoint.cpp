#include "pch.h"
#include "BossEnemyLeftArmJoint.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
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


	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬

	auto leftArm = GetScene()->AddActor<BossEnemyLeftArm>(GetScene(), boss);
	leftArm->SetParent(this);


	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARMJOINT_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARMJOINT_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARMJOINT_ROTATION);
}

BossEnemyLeftArmJoint::~BossEnemyLeftArmJoint()
{
}
