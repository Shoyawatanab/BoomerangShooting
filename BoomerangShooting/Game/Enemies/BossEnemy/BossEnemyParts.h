#pragma once
#include "GameBase/Model/ModelPartsBase.h"

class BossEnemy;

class BossEnemyParts : public ModelPartsBase
{
public:


	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BOSS_ENEMY_PARTS; }

public:
	//コンストラクタ
	BossEnemyParts(Scene* scene, std::string partsName, std::string modelName
		,int hp ,DirectX::SimpleMath::Vector3 boxColliderExtens,float sphereRadius
		,BossEnemy* boss);
	//デストラクタ
	~BossEnemyParts() override  ;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider) override;
	//HP減少
	void HpDecrease(int damage);

	//個別の当たった時の関数
	virtual void OnCollisionEnterActor(ColliderComponent* collider) { UNREFERENCED_PARAMETER(collider); }

private:

	//元のクラス
	BossEnemy* m_bossEnemy;
	//HP
	int m_hp;

};