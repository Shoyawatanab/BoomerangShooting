/*
	Conditions.h
	渡邊翔也
	Decoratorに渡す条件関数の管理クラス
*/

#pragma once
#include "Game/Interface/IBehaviorNode.h"

class CommonResources;
class Player;
class BossEnemy;

class Conditions 
{

public:

	//近距離攻撃の範囲
	static constexpr float CLOSERANGE_ATTACK_DISTANCE{ 7.0f };
	//遠距離攻撃の範囲
	static constexpr float LONGRANGE_ATTACK_DISTANCE{ 18.0f };
	//ジャンプ離攻撃の範囲
	static constexpr float JUMP_ATTACK_DISTANCE{ 18.0f };

	//敵の視野角
	static constexpr float ANGLE{ 60.0f };



public:
	//コンストラクタ
	Conditions( Player* player, BossEnemy* enmey);
	//デストラクタ
	~Conditions();

	//近距離攻撃範囲内かどうか
	bool IsInCloseRangeAttack();
	//遠距離攻撃範囲内かどうか
	bool IsInLongRangeAttack();
	//ジャンプ攻撃範囲内かどうか
	bool IsJumpAttackRange();

	//視界ないかどうか
	bool IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos);
	//HPが最大かどうか
	bool IsMaxHp();
	//HPが半分以上か
	bool IsHPMoreThanHalf();

	//攻撃するかどうか
	bool IsAttack();


private:
	//プレイヤ
	Player* m_palyer;
	//ボス敵
	BossEnemy* m_enemy;

	//IsAttack用変数
	float m_attackCoolTime;

};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/