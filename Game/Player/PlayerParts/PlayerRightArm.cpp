/*
	クラス名     : PlayerRightArm
	説明         : プレイヤの右腕モデル
	補足・注意点 :
*/
#include "pch.h"
#include "PlayerBody.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"



/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
PlayerRightArm::PlayerRightArm(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME, "PlayerArm")
{

	//大きさ
	GetTransform()->SetScale(Params::PLAYER_RIGHTARM_SCALE);
	//位置情報
	GetTransform()->Translate(Params::PLAYER_RIGHTARM_POSITION);
	//回転
	GetTransform()->SetRotate(Params::PLAYER_RIGHTARM_ROTATION);


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerRightArm::~PlayerRightArm()
{
}





