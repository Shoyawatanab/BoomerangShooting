/*
	クラス名     : BossAnimationController
	説明         : ボス敵のアニメーションコントローラー
	補足・注意点 :
*/
#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "Game/Messenger/Messengers.h"

class BossEnemy;

class BossAnimationController : public AnimationController 
{
public:
	//コンストラクタ
	BossAnimationController(BossEnemy* bossEnemy);
	//デストラクタ
	~BossAnimationController() override ;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas)  ;


private:

};