#include "pch.h"
#include "BossEnemyTorso.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyTorso::BossEnemyTorso(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyTorso"
		, Params::BOSSENEMY_TORSO_HP
		, Params::BOSSENEMY_TORSO_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_TORSO_SPHERE_COLLIDER_SIZE
		, boss)
{


	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬
	//Head1‚Ì¶¬
	auto head = GetScene()->AddActor<BossEnemyHead>(GetScene(), boss);
	head->SetParent(this);

	//LeftShouder‚Ì¶¬
	auto leftShouder = GetScene()->AddActor<BossEnemyLeftShoulder>(GetScene(), boss);
	leftShouder->SetParent(this);

	//RightShouder‚Ì¶¬
	auto rightShouder = GetScene()->AddActor<BossEnemyRightShoulder>(GetScene(), boss);
	rightShouder->SetParent(this);

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_TORSO_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_TORSO_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_TORSO_ROTATION);

}

BossEnemyTorso::~BossEnemyTorso()
{
}
