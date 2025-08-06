/*
	クラス名     : BossEnemyTorso
	説明         : ボス敵の胴体モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyTorso.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
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


	//以下追加部位の作成
	//Head1の生成
	auto head = GetScene()->AddActor<BossEnemyHead>(GetScene(), boss);
	head->SetParent(this);

	//LeftShouderの生成
	auto leftShouder = GetScene()->AddActor<BossEnemyLeftShoulder>(GetScene(), boss);
	leftShouder->SetParent(this);

	//RightShouderの生成
	auto rightShouder = GetScene()->AddActor<BossEnemyRightShoulder>(GetScene(), boss);
	rightShouder->SetParent(this);

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_TORSO_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_TORSO_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_TORSO_ROTATION);

}

BossEnemyTorso::~BossEnemyTorso()
{
}
