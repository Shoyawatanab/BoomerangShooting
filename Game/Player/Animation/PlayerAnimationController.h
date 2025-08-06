/*
	クラス名     : PlayerAnimationController
	説明         : プレイヤアニメーションコントローラー
	補足・注意点 :
*/
#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "Game/Messenger/Messengers.h"

class Player;

class PlayerAnimationController : public AnimationController
{
public:
	//コンストラクタ
	PlayerAnimationController(Player* player);
	//デストラクタ
	~PlayerAnimationController() override ;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:

};