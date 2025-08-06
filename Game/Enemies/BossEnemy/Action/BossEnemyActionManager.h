/*
	クラス名     : BossEnemyActionManager
	説明         : ボス敵の行動のマネージャー
	補足・注意点 :
*/
#pragma once
#include "GameBase/Action/ActionManager.h"
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Player;
class BossEnemy;
class BossEnemyBeam;

class BossEnemyActionManager : public ActionManager
{
public:
	//コンストラクタ
	BossEnemyActionManager(BossEnemy* ower,Player* target, BossEnemyBeam* beam);
	//デストラクタ
	~BossEnemyActionManager() override;

	//通知を受け取る関数
	void Notify(SceneMessageType type, void* datas);

private:
	//ボス
	BossEnemy* m_bossEnemy;

};