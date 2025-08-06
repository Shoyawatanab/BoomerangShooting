/*
	クラス名     : BossEnemyBottom
	説明         : ボス敵の尻モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyBottom.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

BossEnemyBottom::BossEnemyBottom(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		,"BossEnemyBottom"
		, Params::BOSSENEMY_BODY_HP
		, Params::BOSSENEMY_BODY_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_BODY_SPHERE_COLLIDER_SIZE
		,boss)
{


	//以下追加部位の作成

	//Pelvisの生成
	auto pelvis = GetScene()->AddActor<BossEnemyPelvis>(GetScene(),boss);
	pelvis->SetParent(this);

	////LeftThighの生成
	auto leftThigh = GetScene()->AddActor<BossEnemyLeftThigh>(GetScene(), boss);
	leftThigh->SetParent(this);

	////RightThighの生成
	auto rightThigh = GetScene()->AddActor<BossEnemyRightThigh>(GetScene(), boss);
	rightThigh->SetParent(this);

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_BODY_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_BODY_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_BODY_ROTATION);
}

BossEnemyBottom::~BossEnemyBottom()
{
}
