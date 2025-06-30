#include "pch.h"
#include "WeaponBase.h"

WeaponBase::WeaponBase(Scene* scene)
	:
	Actor(scene)
	,m_state{WeaponState::BOOMERANG_IDLE}
{
}

/// <summary>
/// デストラクタ
/// </summary>
WeaponBase::~WeaponBase()
{
}

/// <summary>
/// ステートの変更
/// </summary>
/// <param name="nextState">次のステート</param>
void WeaponBase::ChangeState(WeaponState nextState)
{
	//個別のステート変更
	ActorChangeState(nextState);

	//状態の変更
	m_state = nextState;
	
}
