/*
	クラス名     : StageOneInformation
	説明         : セレクトシーンの右の情報(ステージ１の)
	補足・注意点 :
*/
#include "pch.h"
#include "StageOneInformation.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "GameBase/UI/Image.h"



/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
StageOneInformation::StageOneInformation(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;



	//ステージ１の情報
	auto birdEnemy1 = GetScene()->AddActor<Image>(canvas, "BirdEnemy");
	birdEnemy1->GetTransform()->SetPosition(BIRD_ONE_POSITION);
	birdEnemy1->GetTransform()->SetParent(GetTransform());

	auto birdEnemy2 = GetScene()->AddActor<Image>(canvas, "BirdEnemy");
	birdEnemy2->GetTransform()->SetPosition(BIRD_TWO_POSITION);
	birdEnemy2->GetTransform()->SetParent(GetTransform());


}

/// <summary>
/// デストラクタ
/// </summary>
StageOneInformation::~StageOneInformation()
{
}

