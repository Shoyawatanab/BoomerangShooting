/*
	クラス名     : BoomerangDrop
	説明         : ブーメランのドロップの状態
	補足・注意点 :
*/
#pragma once
#include "GameBase/Interface/IState.h"

class BoomerangStateMachine;
class Boomerang;

class BoomerangDrop : public IState
{
public:
	//跳ね返りの力
	static constexpr float BOUNCE_POWER = 3.0f;;

public:
	//コンストラクタ
	BoomerangDrop(BoomerangStateMachine* stateMahine, Boomerang* boomerang);
	//デストラクタ
	~BoomerangDrop() override;

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
};

