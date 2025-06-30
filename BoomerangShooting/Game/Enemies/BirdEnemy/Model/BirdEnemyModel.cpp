#include "pch.h"
#include "BirdEnemyModel.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Enemies/BirdEnemy/BirdEnemyPartss.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
BirdEnemyModel::BirdEnemyModel(Scene* scene)
	:
	ModelBase(scene)
{
	//BODYの作成
	auto body = GetScene()->AddActor<BirdEnemyBody>(GetScene());
	//親子関係を結ぶ
	body->GetTransform()->SetParent(GetTransform());

	//子孫モデルを取得
	auto parts = body->GetAllDescendants();
	//子孫モデルをパーツに登録
	AddParts(parts);
	


}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyModel::~BirdEnemyModel()
{
}
