/*
	クラス名     : PlayerRightFeet
	説明         : プレイヤの右足モデル
	補足・注意点 :
*/
#include "pch.h"
#include "PlayerRightFeet.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
PlayerRightFeet::PlayerRightFeet(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME, "PlayerFeet")
{
	//大きさ
	GetTransform()->SetScale(Params::PLAYER_RIGHTFEET_SCALE);
	//位置情報
	GetTransform()->Translate(Params::PLAYER_RIGHTFEET_POSITION);
	//回転
	GetTransform()->SetRotate(Params::PLAYER_RIGHTFEET_ROTATION);

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerRightFeet::~PlayerRightFeet()
{

}



