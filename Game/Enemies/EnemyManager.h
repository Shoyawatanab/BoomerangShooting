/*
	クラス名     : EnemyManager
	説明         : 敵のマネージャー
	補足・注意点 : 
*/
#pragma once
#include "GameBase/Actor.h"

class Player;

class EnemyManager : public Actor
{
public:

	//全ての敵を返す
	std::vector<Actor*> GetEnemys() { return m_enemys; }
	//ターゲットの敵の取得
	std::vector<Actor*> GetTargets() { return m_targets; }

public:
	//コンストラクタ
	EnemyManager(Scene* scene, Player* player);
	//デストラクタ
	~EnemyManager() override;
	//敵の死亡
	void DeathEnemy(Actor* enemy);
	//ターゲットの追加
	void AddTargets(std::vector<Actor*> targets);

private:

	//データの読み込み
	void LoadData();


private:
	//敵配列
	std::vector<Actor*> m_enemys;
	//プレイヤ
	Player* m_player;
	//ターゲットActor配列　ターゲットマーカーで使用
	std::vector<Actor*> m_targets;

};