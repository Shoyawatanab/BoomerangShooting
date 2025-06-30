#pragma once
#include "GameBase/Action/ActionManager.h"
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Player;
class BossEnemy;
class BossEnemyBeam;

class BossEnemyActionManager : public ActionManager , public IObserver< SceneMessageType>
{
public:
	//コンストラクタ
	BossEnemyActionManager(BossEnemy* ower,Player* target, BossEnemyBeam* beam);
	//デストラクタ
	~BossEnemyActionManager() override;

	//通知を受け取る関数
	void Notify(SceneMessageType type, void* datas) override;

};