#pragma once
#include "GameBase/Actor.h"

class ModelBase;
class EnemyManager;

class EnemyBase : public Actor
{
public:
	//敵マネージャーのセット
	void SetEnemyManager(EnemyManager* manager) { m_manger = manager; }
	//敵マネージャーの取得
	EnemyManager* GetEnemyManger() { return m_manger; }


	//モデルの取得
	ModelBase* GetModel() { return m_model; }
	//モデルのセット
	void SetModel(ModelBase* model) { m_model = model; }
	//HPの取得
	int GetHp() { return m_hp; }
	//HPのセット
	void SetHp(int hp) { m_hp = hp; }
	//最大Hpの取得
	int GetMaxHp() { return m_maxHp; }
	//HP割合の取得
	float GetHpRatio() { return static_cast<float>(m_hp) / m_maxHp; };



public:
	//コンストラクタ
	EnemyBase(Scene* scene,int hp);
	//デストラクタ
	~EnemyBase();

	//HPの減少
	void HpDecrease(int damage);

private:
	//敵マネージャー
	EnemyManager* m_manger;

	//HP
	int m_hp;
	//最大HP
	int m_maxHp;
	//モデル
	ModelBase* m_model;
};

