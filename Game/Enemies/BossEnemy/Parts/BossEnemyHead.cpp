/*
	クラス名     : BossEnemyHead
	説明         : ボス敵の頭モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyHead.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
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

	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_HEAD_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_HEAD_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_HEAD_ROTATION);

	//以下追加部位の作成


}

BossEnemyHead::~BossEnemyHead()
{
}
