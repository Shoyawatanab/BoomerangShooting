#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Player;

class PlayerAnimationController : public AnimationController , public IObserver<SceneMessageType>
{
public:
	//コンストラクタ
	PlayerAnimationController(Player* player);
	//デストラクタ
	~PlayerAnimationController() override ;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) override ;


private:

};