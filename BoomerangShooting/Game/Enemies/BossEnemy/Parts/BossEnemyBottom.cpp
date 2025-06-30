#include "pch.h"
#include "BossEnemyBottom.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
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


	//obb->SetOffsetPosition(DirectX::SimpleMath::Vector3(0, 0.0f, 0));

	//ˆÈ‰º’Ç‰Á•”ˆÊ‚Ìì¬

	//Pelvis‚Ì¶¬
	auto pelvis = GetScene()->AddActor<BossEnemyPelvis>(GetScene(),boss);
	pelvis->SetParent(this);

	////LeftThigh‚Ì¶¬
	auto leftThigh = GetScene()->AddActor<BossEnemyLeftThigh>(GetScene(), boss);
	leftThigh->SetParent(this);

	////RightThigh‚Ì¶¬
	auto rightThigh = GetScene()->AddActor<BossEnemyRightThigh>(GetScene(), boss);
	rightThigh->SetParent(this);

	//ˆÊ’uî•ñ
	GetTransform()->Translate(Params::BOSSENEMY_BODY_POSITION);
	//‘å‚«‚³
	GetTransform()->SetScale(Params::BOSSENEMY_BODY_SCALE);
	//‰ñ“]
	GetTransform()->SetRotate(Params::BOSSENEMY_BODY_ROTATION);
}

BossEnemyBottom::~BossEnemyBottom()
{
}
