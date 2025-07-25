#include "pch.h"
#include "BossEnemyLeftShoulder.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyLeftShoulder::BossEnemyLeftShoulder(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene, PARTS_NAME
		, "BossEnemyShoulder"
		, Params::BOSSENEMY_LEFTSHOULDER_HP
		, Params::BOSSENEMY_LEFTSHOULDER_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTSHOULDER_SPHERE_COLLIDER_SIZE
		, boss)
{



	//以下追加部位の作成
//「LeftArmJoint」を生成する
	auto leftArmJoint = GetScene()->AddActor<BossEnemyLeftArmJoint>(GetScene(), boss);
	leftArmJoint->SetParent(this);


	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_LEFTSHOULDER_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTSHOULDER_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTSHOULDER_ROTATION);


}

BossEnemyLeftShoulder::~BossEnemyLeftShoulder()
{
}
