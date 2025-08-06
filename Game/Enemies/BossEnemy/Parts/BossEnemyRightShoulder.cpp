/*
	クラス名     : BossEnemyRightShoulder
	説明         : ボス敵の右肩モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyRightShoulder.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
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


	//以下追加部位の作成
//RightArmJointの生成
	auto rightArmJoint = GetScene()->AddActor<BossEnemyRightArmJoint>(GetScene(), boss);
	rightArmJoint->SetParent(this);

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTSHOULDER_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTSHOULDER_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTSHOULDER_ROTATION);



}

BossEnemyRightShoulder::~BossEnemyRightShoulder()
{
}
