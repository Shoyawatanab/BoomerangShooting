/*
	クラス名     : PlayerBody
	説明         : プレイヤの胴体モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Player/PlayerParts.h"



// 「砲塔」クラスを定義する
class PlayerBody : public PlayerParts
{

private:

	//パーツ名
	static constexpr const char PARTS_NAME[] = "Body";


public:
	//コンストラクタ
	PlayerBody(Scene* scene);           //+Zに向いているときの回転情報
	//デストラクタ
	~PlayerBody() override;

	//void OnCollisionEnter(Collider* collider) override;

};

