#include "pch.h"
#include "RigidbodyComponent.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "Game/Params.h"


#include "GameBase/Common/Commons.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="actor">所有者</param>
RigidbodyComponent::RigidbodyComponent(Actor* actor)
	:
	Component(actor)
	,
	m_velocity{}
	,m_addforce{}
	,m_isFixed{false}
	,m_deceleration{1.0f}
	,m_isGravity{true}
{

	//マネージャーに追加
	auto rigidbodyManager = actor->GetScene()->GetRigidbodyManager();
	rigidbodyManager->AddRigidbody(this);

}

/// <summary>
/// デストラクタ
/// </summary>
RigidbodyComponent::~RigidbodyComponent()
{
	//削除
	auto rigidbodyManager = GetActor()->GetScene()->GetRigidbodyManager();
	rigidbodyManager->RemoveRigidbody(this);

}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void RigidbodyComponent::Update(const float& deltaTime)
{

	

	using namespace DirectX::SimpleMath;

	//固定なら
	if (m_isFixed)
	{
		return;
	}

	//重力計算
	if(m_isGravity)
	{
		//重力加算
		AddForce(Vector3(0.0f, Params::GRAVITY * deltaTime,0.0f));
	}

	//速度の計算
	auto velocity2 =  m_velocity + m_addforce * deltaTime;

	//オブジェクトの移動
	GetActor()->GetTransform()->Translate(velocity2);

	//減速させる
	m_velocity = Vector3::Zero;

	//摩擦の原減速
	m_addforce.x *= m_deceleration;
	m_addforce.z *= m_deceleration;






}





