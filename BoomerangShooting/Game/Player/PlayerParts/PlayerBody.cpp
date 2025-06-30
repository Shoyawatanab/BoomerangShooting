#include "pch.h"
#include "PlayerBody.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
PlayerBody::PlayerBody(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME,"PlayerBody")
{

	//位置情報
	GetTransform()->Translate(Params::PLAYER_BODY_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::PLAYER_BODY_SCALE);
	//回転
	GetTransform()->SetRotate(Params::PLAYER_BODY_ROTATION);


	//Headの作成
	auto head = GetScene()->AddActor<PlayerHead>(GetScene());
	//親の登録
	//head->GetTransform()->SetParent(GetTransform());
	head->SetParent(this);

	//LeftArmの作成
	auto leftArm = GetScene()->AddActor<PlayerLeftArm>(GetScene());
	//親の登録
	//leftArm->GetTransform()->SetParent(GetTransform());
	leftArm->SetParent(this);

	//RightArmの作成
	auto rightArm = GetScene()->AddActor<PlayerRightArm>(GetScene());
	//親の登録
	//rightArm->GetTransform()->SetParent(GetTransform());
	rightArm->SetParent(this);


	//LeftFeetの作成
	auto leftfeet = GetScene()->AddActor<PlayerLeftFeet>(GetScene());
	//親の登録
	//leftfeet->GetTransform()->SetParent(GetTransform());
	leftfeet->SetParent(this);


	//rightFeetの作成
	auto rightfeet = GetScene()->AddActor<PlayerRightFeet>(GetScene());
	//親の登録
	//rightfeet->GetTransform()->SetParent(GetTransform());
	rightfeet->SetParent(this);



}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBody::~PlayerBody()
{
}



