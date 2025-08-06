/*
	クラス名     : BossEnemyLeftLeg
	説明         : ボス敵の左足モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyLeftLeg.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"

BossEnemyLeftLeg::BossEnemyLeftLeg(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyLeg"
		, Params::BOSSENEMY_LEFTLEG_HP
		, Params::BOSSENEMY_LEFTLEG_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTLEG_SPHERE_COLLIDER_SIZE
		, boss)
{

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_LEFTLEG_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTLEG_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTLEG_ROTATION);

	//以下追加部位の作成


}

BossEnemyLeftLeg::~BossEnemyLeftLeg()
{
}
