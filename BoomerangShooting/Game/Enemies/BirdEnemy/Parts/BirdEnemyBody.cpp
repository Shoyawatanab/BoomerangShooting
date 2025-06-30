#include "pch.h"
#include "BirdEnemyBody.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Enemies/BirdEnemy/BirdEnemyPartss.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
BirdEnemyBody::BirdEnemyBody(Scene* scene)
	:
	BirdEnemyPars(scene,PARTS_NAME,"BirdEnemyBody")
{
	//左羽の作成
	auto leftFeather = GetScene()->AddActor<BirdEnemyLeftFeather>(GetScene());
	//親子関係を結ぶ　
	leftFeather->SetParent(this);
	//右羽の作成
	auto rightFeather = GetScene()->AddActor<BirdEnemyRightFeather>(GetScene());
	//親子関係を結ぶ
	rightFeather->SetParent(this);

	//位置情報
	GetTransform()->Translate(Params::BIRDENEMY_BODY_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BIRDENEMY_BODY_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BIRDENEMY_BODY_ROTATION);

}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBody::~BirdEnemyBody()
{
}
