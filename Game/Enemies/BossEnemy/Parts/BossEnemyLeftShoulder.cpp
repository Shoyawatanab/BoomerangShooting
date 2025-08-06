/*
	クラス名     : BossEnemyLeftShoulder
	説明         : ボス敵の左肩モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyLeftShoulder.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="boss">ボス</param>
BossEnemyLeftShoulder::BossEnemyLeftShoulder(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene, PARTS_NAME
		, "BossEnemyShoulder"
		//, Params::BOSSENEMY_LEFTSHOULDER_HP
		, 10
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

/// <summary>
/// コンストラク
/// </summary>
BossEnemyLeftShoulder::~BossEnemyLeftShoulder()
{
}

/// <summary>
/// 部位破壊時の処理
/// </summary>
void BossEnemyLeftShoulder::PartsDestruction()
{

	//親子関係をなくす
	//GetTransform()->SetParent(nullptr);


	////重力の追加
	//auto rigidBody = GetComponent<RigidbodyComponent>();
	//rigidBody->SetActive(true);
	

	
}
