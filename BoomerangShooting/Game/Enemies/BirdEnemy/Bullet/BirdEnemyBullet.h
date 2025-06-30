#pragma once
#include "GameBase/Actor.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStateMachine.h"

class BirdEnemy;
class SoundComponent;


class  BirdEnemyBullet : public Actor
{
public:

	//当たり判定の大きさ
	static constexpr float SPHERE_COLLIDER_SIZE = 0.5f;
	static constexpr DirectX::SimpleMath::Vector3  BOX_COLLIDER_SIZE {0.3f, 0.3f, 0.3f};

public:

	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BIRD_BULLET; }

	//ステートマシーンの取得
	BirdEnemyBulletStateMachine* GetStateMachine() { return m_stateMachine.get(); }

public:
	//コンストラク
	BirdEnemyBullet(Scene* scene, BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyBullet() override;

	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider) override;


private:

	//所有者
	BirdEnemy* m_birdEnemy;
	//ステートマシン
	std::unique_ptr<BirdEnemyBulletStateMachine> m_stateMachine;
	//爆発音
	SoundComponent* m_explosionSE;

};

