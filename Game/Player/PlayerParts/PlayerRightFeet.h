/*
	クラス名     : PlayerRightFeet
	説明         : プレイヤの右足モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Player/PlayerParts.h"



// 「砲塔」クラスを定義する
class PlayerRightFeet : public PlayerParts
{
private:

	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightFeet";

public:
	//コンストラクタ
	PlayerRightFeet(Scene* scene);
	//デストラクタ
	~PlayerRightFeet() override;



};

