/*
* プレイヤの左足クラス
*/
#pragma once
#include "Game/Player/PlayerParts.h"



// 「砲塔」クラスを定義する
class PlayerLeftFeet : public PlayerParts
{
private:

	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftFeet";

public:
	//コンストラクタ
	PlayerLeftFeet(Scene* scene);
	//デストラクタ
	~PlayerLeftFeet() override;




};

