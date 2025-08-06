/*
	クラス名     : PlayerParts
	説明         : プレイヤのパーツの基底クラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Model/ModelPartsBase.h"


class PlayerParts  :public ModelPartsBase
{

public:

	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::PLAYER_PARTS; }

public:

	//コンストラクタ
	PlayerParts(Scene* scene,std::string partsName,std::string modelName);
	//デストラクタ
	~PlayerParts() override;

private:



};