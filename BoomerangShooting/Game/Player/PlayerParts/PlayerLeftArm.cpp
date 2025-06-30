#include "pch.h"
#include "PlayerLeftArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
PlayerLeftArm::PlayerLeftArm(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME, "PlayerArm")
{

	//大きさ
	GetTransform()->SetScale(Params::PLAYER_LEFRARM_SCALE);
	//位置情報
	GetTransform()->Translate(Params::PLAYER_LEFRARM_POSITION);
	//回転
	GetTransform()->SetRotate(Params::PLAYER_LEFRARM_ROTATION);

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerLeftArm::~PlayerLeftArm()
{
}


