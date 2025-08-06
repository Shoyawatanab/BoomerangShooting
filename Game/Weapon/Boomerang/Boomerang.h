/*
	クラス名     : Boomerang
	説明         : ブーメラン
	補足・注意点 :
*/
#pragma once
#include "Game/Weapon/WeaponBase.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"

class Player;
class SoundComponent;


class Boomerang : public WeaponBase<BoomerangState>
{
public:

	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BOOMERANG; }
	//ステートマシーンの取得
	BoomerangStateMachine* GetStateMAchine() { return m_stateMachine.get(); }
	//１フレ前の座標を取得
	const DirectX::SimpleMath::Vector3& GetLastPosition() { return m_lastPosition; }

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
	void ActorChangeState(BoomerangState nextState) override;

private:

	//回収
	void PickUp();

private:
	//ステートマシーン
	std::unique_ptr<BoomerangStateMachine> m_stateMachine;

	//1フレ前の座標
	DirectX::SimpleMath::Vector3 m_lastPosition;

	//打撃音
	SoundComponent* m_strikeSE;

};

