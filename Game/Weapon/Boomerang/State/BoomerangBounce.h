/*
	クラス名     : BoomerangBounce
	説明         : ブーメランの跳ね返りの状態
	補足・注意点 :
*/
#pragma once
#include "GameBase/Interface/IState.h"

class BoomerangStateMachine;
class Boomerang;

class BoomerangBounce : public IState
{
public:
	//跳ね返りの力
	static constexpr float BOUNCE_POWER = 3.0f;;

public:
	//コンストラクタ
	BoomerangBounce(BoomerangStateMachine* stateMahine, Boomerang* boomerang);
	//デストラクタ
	~BoomerangBounce() override;

	// 更新する
	void Update(const float& deltaTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:
	//ブーメラン
	Boomerang* m_boomerang;
	//ステートマシーン
	BoomerangStateMachine* m_stateMahine;
	//弾かれる方向
	DirectX::SimpleMath::Vector3 m_bounceDirection;
};

