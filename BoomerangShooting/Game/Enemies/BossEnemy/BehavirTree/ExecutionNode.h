/*
	ExecutionNode.h
	渡邊翔也
	実行ノードに渡す処理の関数の管理クラス
*/

#pragma once
#include "Game/Interface/IBehaviorNode.h"
#include  <unordered_map>

class CommonResources;
class Player;
class BossEnemy;


class ExecutionNode
{

public:
	//コンストラクタ
	ExecutionNode(Player* player, BossEnemy* enmey);
	//デストラクタ
	~ExecutionNode();
	
	//ビーム攻撃
	IBehaviorNode::State BossEnemyBeamAction();
	//ジャンプ攻撃
	IBehaviorNode::State BossEnemyJumpAttackAction();
	//歩く
	IBehaviorNode::State BossEnemyWalking();
	//振り下ろし攻撃
	IBehaviorNode::State BossEnemySwingDown();


private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	BossEnemy* m_enemy;


};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/