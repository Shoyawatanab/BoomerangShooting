#include "pch.h"
#include "BossEnemyModel.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"
#include "GameBase/Component/Transform/Transform.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
BossEnemyModel::BossEnemyModel(Scene* scene, BossEnemy* boss)
	:
	ModelBase(scene)
{

	using namespace DirectX::SimpleMath;

	//Bodyの作成
	auto body = GetScene()->AddActor<BossEnemyBottom>(GetScene(),boss);
	body->GetTransform()->SetParent(GetTransform());
	//子孫モデルを取得
	auto parts = body->GetAllDescendants();
	//子孫モデルをパーツに登録
	AddParts(parts);

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyModel::~BossEnemyModel()
{
}


