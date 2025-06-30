#include "pch.h"
#include "PlayerLeftFeet.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
PlayerLeftFeet::PlayerLeftFeet(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME, "PlayerFeet")

{

	//大きさ
	GetTransform()->SetScale(Params::PLAYER_LEFRFEET_SCALE);
	//位置情報
	GetTransform()->Translate(Params::PLAYER_LEFRFEET_POSITION);
	//回転
	GetTransform()->SetRotate(Params::PLAYER_LEFRFEET_ROTATION);


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerLeftFeet::~PlayerLeftFeet()
{
}



