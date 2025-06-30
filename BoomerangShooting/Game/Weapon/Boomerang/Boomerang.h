#pragma once
#include "Game/Weapon/WeaponBase.h"

class BoomerangStateMachine;
class Player;

class Boomerang : public WeaponBase
{
public:

	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BOOMERANG; }
	//ステートマシーンの取得
	BoomerangStateMachine* GetStateMAchine() { return m_stateMachine.get(); }
public:
	//コンストラクタ
	Boomerang(Scene* scene, Player* player);
	//デストラクタ
	~Boomerang() override;
	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider);
	//ステート変更
	void ActorChangeState(WeaponState nextState) override;

private:
	std::unique_ptr<BoomerangStateMachine> m_stateMachine;

};

