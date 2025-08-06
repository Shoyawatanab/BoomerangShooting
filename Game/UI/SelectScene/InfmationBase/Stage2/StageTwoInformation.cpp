/*
	クラス名     : StageTwoInformation
	説明         : セレクトシーンの右の情報(ステージ2の)
	補足・注意点 :
*/
#include "pch.h"
#include "StageTwoInformation.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "GameBase/UI/Image.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
StageTwoInformation::StageTwoInformation(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	
	using namespace DirectX::SimpleMath;


	//ボス画像
	auto boss = GetScene()->AddActor<Image>(canvas, "BossEnemy");
	boss->GetTransform()->SetParent(GetTransform());


}

/// <summary>
/// デストラクタ
/// </summary>
StageTwoInformation::~StageTwoInformation()
{
}



