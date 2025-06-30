#pragma once
#include "GameBase/Actor.h"

class Player;

class EnemyManager : public Actor
{
public:
	//全ての敵を返す
	std::vector<Actor*> GetEnemys() { return m_enemys; }

public:
	//コンストラクタ
	EnemyManager(Scene* scene, Player* player);
	//デストラクタ
	~EnemyManager() override;

	//敵の死亡
	void DeathEnemy(Actor* enemy);

private:

	//データの読み込み
	void LoadData();


private:

	std::vector<Actor*> m_enemys;

	Player* m_player;

};