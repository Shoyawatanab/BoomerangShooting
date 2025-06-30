/*
* プレイヤの右足クラス
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

