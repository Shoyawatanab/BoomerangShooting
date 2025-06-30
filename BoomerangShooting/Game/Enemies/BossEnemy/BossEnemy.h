/*
* プレイヤクラス　
*/

#pragma once
#include"Game/Enemies/EnemyBase.h"

class BossBehaviorTree;
class Player;
class RigidbodyComponent;
class AnimatorComponent;
class BossEnemyModel;
class BossEnemyActionManager;



class BossEnemy : public EnemyBase 
{
public:

	//着地しているか　true　着地してる　false　してない
	bool GetIsGround() const { return m_isGround; }


	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BOSS_ENEMY; }

	AnimatorComponent* GetAnimation() { return m_animation; }

public:

	//コンストラクタ
	BossEnemy(Scene* scene , DirectX::SimpleMath::Vector3 scale
		,DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotation
		,Player* player);
	//デストラクタ
	~BossEnemy() override;

	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider) override;

	//当たり続けているときの呼び出される
	void OnCollisionStay(ColliderComponent* collider) override;

	//衝突が終了したときに呼び出される
	void OnCollisionExit(ColliderComponent* collider) override;

	//ダメージを食らったとき
	void AddDamage(int damage);

	//回転
	void Rotation(const float& deltaTime);

private:

	//着地したとき
	void Landing();

private:

	//ビヘイビアツリー
	std::unique_ptr<BossBehaviorTree> m_behavior;


	//重力
	RigidbodyComponent* m_rigidBody;
	//アニメーション
	AnimatorComponent* m_animation;
	//アクションマネージャー
	std::unique_ptr<BossEnemyActionManager> m_actionManager;
	//着地しているか
	bool m_isGround;
	//プレイヤ
	Player* m_player;
};


