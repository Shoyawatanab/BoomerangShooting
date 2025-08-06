/*
	クラス名     : PlayerModel
	説明         : プレイヤモデル
	補足・注意点 :
*/
#pragma once
#include "GameBase/Model/ModelBase.h"


class PlayerModel : public ModelBase
{
public:
	//コンストラクタ
	PlayerModel(Scene* scene);
	//でストリング
	~PlayerModel() override;

};
