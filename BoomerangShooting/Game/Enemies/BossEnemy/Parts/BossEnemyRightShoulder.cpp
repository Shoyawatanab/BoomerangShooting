#include "pch.h"
#include "BossEnemyRightShoulder.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightShoulder::BossEnemyRightShoulder(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyShoulder"
		, Params::BOSSENEMY_RIGHTSHOULDER_HP
		, Params::BOSSENEMY_RIGHTSHOULDER_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_RIGHTSHOULDER_SPHERE_COLLIDER_SIZE
		, boss)
{


	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
//RightArmJoint‚Ì¶¬
	auto rightArmJoint = GetScene()->AddActor<BossEnemyRightArmJoint>(GetScene(), boss);
	rightArmJoint->SetParent(this);

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTSHOULDER_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTSHOULDER_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTSHOULDER_ROTATION);



}

BossEnemyRightShoulder::~BossEnemyRightShoulder()
{
}
