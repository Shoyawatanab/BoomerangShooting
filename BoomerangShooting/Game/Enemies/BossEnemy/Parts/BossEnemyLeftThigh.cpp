#include "pch.h"
#include "BossEnemyLeftThigh.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
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



	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
	//LeftLeg‚Ì¶¬
	auto leftLeg = GetScene()->AddActor<BossEnemyLeftLeg>(GetScene(), boss);
	leftLeg->SetParent(this);

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_LEFTTHIGH_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTTHIGH_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTTHIGH_ROTATION);

}

BossEnemyLeftThigh::~BossEnemyLeftThigh()
{
}
