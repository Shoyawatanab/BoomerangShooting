/*
	クラス名     : EnemyBase
	説明         : 敵の基底クラス
	補足・注意点 : 全ての敵の基底にする
*/
#include "pch.h"
#include "EnemyBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="hp">HP</param>
EnemyBase::EnemyBase(Scene* scene, int hp, EnemyManager* manager)
	:
	Actor(scene)
	,m_hp{hp}
	,m_model{}
	,m_maxHp{hp}
	,m_manger{manager}
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
