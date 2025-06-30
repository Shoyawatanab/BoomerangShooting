#include "pch.h"
#include "BossEnemyPelvis.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyPelvis::BossEnemyPelvis(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyPelvis"
		, Params::BOSSENEMY_PELVIS_HP
		, Params::BOSSENEMY_PELVIS_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_PELVIS_SPHERE_COLLIDER_SIZE
		, boss)
{




	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
//Torso‚Ì¶¬
	auto torso = GetScene()->AddActor<BossEnemyTorso>(GetScene(), boss);
	torso->SetParent(this);

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_PELVIS_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_PELVIS_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_PELVIS_ROTATION);



}

BossEnemyPelvis::~BossEnemyPelvis()
{
}
