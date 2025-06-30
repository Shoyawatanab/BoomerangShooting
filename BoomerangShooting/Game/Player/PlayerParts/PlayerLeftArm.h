/*
* プレイヤの左腕クラス
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

