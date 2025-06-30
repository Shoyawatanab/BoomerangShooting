#include "pch.h"
#include "Conditions.h"
#include "GameBase/Common/Commons.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Params.h"
#include "GameBase/Component/Components.h"
#include "Game/MathUtil.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="player">プレイヤ</param>
/// <param name="enemy">ボス敵</param>
Conditions::Conditions(Player* player, BossEnemy* enemy)
	:
	m_palyer{ player },
	m_enemy{ enemy },
	m_attackCoolTime{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
Conditions::~Conditions()
{

}





/// <summary>
/// 近距離攻撃範囲内かどうか
/// </summary>
/// <returns>ture 範囲内  false　範囲外　</returns>
bool Conditions::IsInCloseRangeAttack()
{
	using namespace DirectX::SimpleMath;


	//座標の取得
	Vector3 PlayerPosition = m_palyer->GetTransform()->GetPosition();
	Vector3 EnemyPosition = m_enemy->GetTransform()->GetPosition();

	//Y座標を統一する
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//距離を求める
	float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	//攻撃範囲内かどうか
	if(Distance < CLOSERANGE_ATTACK_DISTANCE)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 遠距離攻撃範囲内かどうか
/// </summary>
/// <returns>true  範囲内  false　範囲外　</returns>
bool Conditions::IsInLongRangeAttack()
{
	using namespace DirectX::SimpleMath;

	//座標の取得
	Vector3 PlayerPosition = m_palyer->GetTransform()->GetPosition();
	Vector3 EnemyPosition = m_enemy->GetTransform()->GetPosition();

	//Y座標を統一する
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//距離を求める
	float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	//攻撃範囲内かどうか
	if (Distance < LONGRANGE_ATTACK_DISTANCE)
	{
		return true;
	}


	return false;
}

/// <summary>
/// ジャンプ攻撃範囲内かどうか
/// </summary>
/// <returns>ture : 範囲内  false :　範囲外</returns>
bool Conditions::IsJumpAttackRange()
{
	using namespace DirectX::SimpleMath;

	//座標の取得
	Vector3 PlayerPosition = m_palyer->GetTransform()->GetPosition();
	Vector3 EnemyPosition = m_enemy->GetTransform()->GetPosition();

	//Y座標を統一する
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//距離を求める
	float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	//攻撃範囲内かどうか
	if (Distance < JUMP_ATTACK_DISTANCE)
	{
		return true;
	}


	return false;

}


/// <summary>
///  敵がプレイヤの視界に入っているかどうか
/// </summary>
/// <param name="playerPos">プレイヤ座標</param>
/// <param name="playerForward">プレイヤの向いている方向</param>
/// <param name="enemyPos">敵座標</param>
/// <returns>true ：ない　false 外</returns>
bool Conditions::IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//角度をラジアンに変換
	float radianViewAngle = XMConvertToRadians(ANGLE);
	float cosViewAngle = cos(radianViewAngle / 2);

	//敵へのベクトルの計算
	Vector3 enemyVector = enemyPos - playerPos;
	enemyVector.Normalize();
	enemyVector.y = 0.0f;

	//ドット積の計算
	float dotProduct = enemyVector.Dot(playerForward);

	return dotProduct >= cosViewAngle;

}

/// <summary>
/// HPが最大かどうか
/// </summary>
/// <returns>ture : 最大 false:最大じゃない</returns>
bool Conditions::IsMaxHp()
{


	if (m_enemy->GetHp() == Params::BOSSENEMY_MAX_HP)
	{
		return true;
	}

	return false;
}

/// <summary>
/// HPが半分以上かどうか
/// </summary>
/// <returns>true : 半分以上 false :半分未満</returns>
bool Conditions::IsHPMoreThanHalf()
{

	if (m_enemy->GetHp() >= Params::BOSSENEMY_MAX_HP / 2)
	{
		return true;
	}

	
	return false;
}

/// <summary>
/// 攻撃するかどうか
/// </summary>
/// <returns>ture : 攻撃　false : 攻撃しない</returns>
bool Conditions::IsAttack()
{

	float ratio =MathUtil::GetRandom(0,100);

	if (ratio >= 30)
	{
		return true;
	}



	return false;
}



