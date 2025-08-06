/*
	クラス名     : PlayerParts
	説明         : プレイヤのパーツの基底クラス
	補足・注意点 :
*/
#include "pch.h"
#include "PlayerParts.h"



PlayerParts::PlayerParts(Scene* scene, std::string partsName, std::string modelName)
	:
	ModelPartsBase(scene,partsName,modelName)
{



}

/// <summary>
/// デストラクタ
/// </summary>
PlayerParts::~PlayerParts()
{
}
