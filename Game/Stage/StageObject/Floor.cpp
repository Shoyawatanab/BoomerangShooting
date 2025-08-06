/*
	クラス名     : Floor
	説明         : 床
	補足・注意点 :
*/
#include "pch.h"
#include "Floor.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="parameter">パラメーター</param>
Floor::Floor(Scene* scene, StageFactory::StageParameter parameter)
	:
	Actor(scene)
{

	GetTransform()->SetPosition(parameter.Position);
	GetTransform()->SetScale(parameter.Scale);
	GetTransform()->SetRotate(parameter.Rotation);

	//モデルコンポーネントの追加
	AddComponent<ModelComponent>(this, "Floor");
	//当たり判定コンポーネントの追加　AABB
	AddComponent<AABB>(this, CollisionType::FIXED
		,BOX_COLLIDER_SIZE, SPHERE_COLLIDER_SIZE);
	
	
}

/// <summary>
/// デストラクタ
/// </summary>
Floor::~Floor()
{
}
