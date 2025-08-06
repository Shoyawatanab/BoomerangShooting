/*
	クラス名     : BossEnemyRightArmJoint
	説明         : ボス敵の右腕関節モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyRightArmJoint.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyRightArmJoint::BossEnemyRightArmJoint(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyArmJoint"
		, Params::BOSSENEMY_RIGHTARMJOINT_HP
		, Params::BOSSENEMY_RIGHTARMJOINT_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_RIGHTARMJOINT_SPHERE_COLLIDER_SIZE
		, boss)
{
	


	//以下追加部位の作成
//RightArmの生成
	auto rightArm = GetScene()->AddActor<BossEnemyRightArm>(GetScene(), boss);
	rightArm->SetParent(this);

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTARMJOINT_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTARMJOINT_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTARMJOINT_ROTATION);



}

BossEnemyRightArmJoint::~BossEnemyRightArmJoint()
{
}
