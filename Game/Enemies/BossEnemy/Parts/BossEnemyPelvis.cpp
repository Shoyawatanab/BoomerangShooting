/*
	クラス名     : BossEnemyPelvis
	説明         : ボス敵の腰モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyPelvis.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
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


	//以下追加部位の作成
//Torsoの生成
	auto torso = GetScene()->AddActor<BossEnemyTorso>(GetScene(), boss);
	torso->SetParent(this);

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_PELVIS_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_PELVIS_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_PELVIS_ROTATION);



}

BossEnemyPelvis::~BossEnemyPelvis()
{
}
