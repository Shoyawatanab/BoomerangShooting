#pragma once
#include "GameBase/Animation/AnimationController.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class BossEnemy;

class BossAnimationController : public AnimationController , public IObserver<SceneMessageType>
{
public:
	//コンストラクタ
	BossAnimationController(BossEnemy* bossEnemy);
	//デストラクタ
	~BossAnimationController() override ;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) override ;


private:

};