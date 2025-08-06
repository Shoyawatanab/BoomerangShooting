/*
	クラス名     : PlayerLeftArm
	説明         : プレイヤの左腕モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Player/PlayerParts.h"




// 「砲塔」クラスを定義する
class PlayerLeftArm : public PlayerParts
{
private:
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftArm";

public:
	//コンストラクタ
	PlayerLeftArm(Scene* scene);
	//デストラクタ
	~PlayerLeftArm() override;



};

