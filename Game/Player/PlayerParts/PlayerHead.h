/*
	クラス名     : PlayerHead
	説明         : プレイヤの頭モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Player/PlayerParts.h"


// 「砲塔」クラスを定義する
class PlayerHead : public PlayerParts
{
private:
	//パーツ名
	static constexpr const char PARTS_NAME[] = "Head";

public:
	//コンストラクタ
	PlayerHead(Scene* scene);
	//デストラクタ
	~PlayerHead() override;

};

