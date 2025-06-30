#include "pch.h"
#include "EnemyBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="hp">HP</param>
EnemyBase::EnemyBase(Scene* scene, int hp)
	:
	Actor(scene)
	,m_hp{hp}
	,m_model{}
	,m_maxHp{hp}
	,m_manger{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBase::~EnemyBase()
{
}

/// <summary>
/// HPの減少
/// </summary>
/// <param name="damage">ダメージ</param>
void EnemyBase::HpDecrease(int damage)
{
	//HPの減少
	m_hp -= damage;
	//０以下にならないように
	m_hp = std::max(m_hp, 0);
}
