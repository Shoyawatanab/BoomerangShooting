/*
	クラス名     : BossEnemy
	説明         : ボス敵のパーツの基底クラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Model/ModelPartsBase.h"

class CommonResources;

class BossEnemy;
class Camera;

class BossEnemyParts : public ModelPartsBase
{
public:


	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BOSS_ENEMY_PARTS; }

	//ボス敵の取得
	BossEnemy* GetBossEnemy() { return m_bossEnemy; }

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

	//部位破壊時の処理
	virtual void PartsDestruction() {}

private:

	//描画
	void Render(const Camera& camera);

private:
	//共通リソース
	CommonResources* m_commonResources;

	//元のクラス
	BossEnemy* m_bossEnemy;
	//HP
	int m_hp;

};