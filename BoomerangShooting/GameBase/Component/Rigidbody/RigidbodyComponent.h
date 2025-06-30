#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"


class RigidbodyComponent : public Component
{

public:
	//速度取得
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	//速度設定
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	//追加速度取得
	DirectX::SimpleMath::Vector3 GetAddforce() const { return m_addforce; }
	//追加速度設定
	void SetAddForce(const DirectX::SimpleMath::Vector3& addforce) { m_addforce = addforce; }
	//追加速度増加
	void AddForce(const DirectX::SimpleMath::Vector3& addforce) { m_addforce += addforce; }
	//固定フラグ取得
	bool GetFixed() const { return m_isFixed; }
	//固定フラグ設定
	void SetFixed(float fixed) { m_isFixed = fixed; }
	//減速率のセット
	void  SetDeceleration(const float& deceleration) { m_deceleration = deceleration; }
	//重力フラグの取得
	bool GetIsGravity() const { return m_isGravity; }
	//重力フラグのセット
	void SetIsGravity(bool isGravity) { m_isGravity = isGravity; }
	//重力のリセット
	void ResetGravity() { m_addforce.y = 0.0f; }
public:
	//コンストラクタ
	RigidbodyComponent(Actor* actor);
	//デストラクタ
	~RigidbodyComponent() override;
	//更新処理
	void Update(const float& deltaTime) override;

private:
	//速度
	DirectX::SimpleMath::Vector3 m_velocity;
	//
	DirectX::SimpleMath::Vector3 m_addforce;
	//固定かどうか　true：　固定　false：　非固定
	bool m_isFixed;
	//減速率
	float m_deceleration;
	//重力があるかどうか true : あり false : なし
	bool m_isGravity;

};