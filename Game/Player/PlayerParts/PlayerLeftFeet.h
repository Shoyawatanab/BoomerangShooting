/*
	クラス名     : PlayerLeftFeet
	説明         : プレイヤの左足モデル
	補足・注意点 :
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

