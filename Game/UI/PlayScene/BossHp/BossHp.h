/*
	クラス名     : BossHp
	説明         : ボスHPのUI
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;

class BossHp : public Actor 
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION{640, 50.5, 0};
	//背景の大きさ
	static constexpr DirectX::SimpleMath::Vector3 BACKGRAUND_SCALE{1, 0.9, 0};
	//座標
	static constexpr DirectX::SimpleMath::Vector3 HP_BAR_SCALE{1, 0.85, 0};
public:
	//コンストラクタ
	BossHp(Canvas* canvas);
	//デストラクタ
	~BossHp() override ;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:

	Image* m_backGraund;

	Image* m_hpBar;

};

