#include "pch.h"
#include "BossEnemyHead.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

BossEnemyHead::BossEnemyHead(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyHead"
		, Params::BOSSENEMY_HEAD_HP
		, Params::BOSSENEMY_HEAD_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_HEAD_SPHERE_COLLIDER_SIZE
		,boss)
{
	
	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_HEAD_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_HEAD_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_HEAD_ROTATION);

	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬


}

BossEnemyHead::~BossEnemyHead()
{
}
