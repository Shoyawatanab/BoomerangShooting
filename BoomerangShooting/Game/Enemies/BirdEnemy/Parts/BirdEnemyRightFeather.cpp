#include "pch.h"
#include "BirdEnemyRightFeather.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
BirdEnemyRightFeather::BirdEnemyRightFeather(Scene* scene)
	:
	BirdEnemyPars(scene,PARTS_NAME,"BirdEnemyFeather")
{

	//位置情報
	GetTransform()->Translate(Params::BIRDENEMY_RIGHTFEATHER_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BIRDENEMY_RIGHTFEATHER_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BIRDENEMY_RIGHTFEATHER_ROTATION);
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyRightFeather::~BirdEnemyRightFeather()
{
}