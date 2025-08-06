/*
	クラス名     : PlayerHead
	説明         : プレイヤの頭モデル
	補足・注意点 :
*/
#include "pch.h"
#include "PlayerHead.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
PlayerHead::PlayerHead(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME,"PlayerHead")
{
	//大きさ
	GetTransform()->SetScale(Params::PLAYER_HEAD_SCALE);
	//位置情報
	GetTransform()->Translate(Params::PLAYER_HEAD_POSITION);
	//回転
	GetTransform()->SetRotate(Params::PLAYER_HEAD_ROTATION);


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerHead::~PlayerHead()
{
}



