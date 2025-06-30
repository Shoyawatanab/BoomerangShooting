#include "pch.h"
#include "BossEnemyRightLeg.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
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


	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTLEG_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTLEG_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTLEG_ROTATION);

	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬


}

BossEnemyRightLeg::~BossEnemyRightLeg()
{
}
