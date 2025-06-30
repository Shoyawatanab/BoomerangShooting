/*
	BossBehaviorTree.h
	渡邊翔也
	ビヘイビアツリーのRootに当たるクラス
*/
#pragma once
#include "Game/Interface/ICompositeNode.h"

class CommonResources;
class Root;
class Player;
class BossEnemy;
class ExecutionNode;
class Conditions;
class ActionNode;
class DecoratorNode;

class BossBehaviorTree
{
public:
	//コンストラクタ
	BossBehaviorTree(Player* player, BossEnemy* enemy);
	//デストラクタ
	~BossBehaviorTree();
	//更新
	void Update(const float& deltaTime);

private:
	//振り下ろし攻撃の作成
	std::unique_ptr<ActionNode> CreateSwingDownActionNode();
	//ビーム攻撃の作成
	std::unique_ptr<ActionNode> CreateBeamAttackActionNode();
	//歩きの作成
	std::unique_ptr<ActionNode> CreateWalkingActionNode();
	//ジャンプ攻撃の作成
	std::unique_ptr<ActionNode> CreateJumpAttackActionNode();


	//HPが半分あるかどうかのDecoratorの作成
	std::unique_ptr<DecoratorNode> CreateIsHPMoreThanHalfDecorator();

	//近距離攻撃の範囲内かどうかのDecoratorの作成
	std::unique_ptr<DecoratorNode> CreateCloseRangeAttackDecorator();
	//遠距離攻撃の範囲内かどうかのDecoratorの作成
	std::unique_ptr<DecoratorNode> CreateLongRangeAttackDecorator();
	//ジャンプ攻撃の範囲内かどうかのDecoratorの作成
	std::unique_ptr<DecoratorNode> CreateJumpAttackDecorator();

private:

	//ノードツリーの作成
	void CreateNodeTree();

private:
	//共通リソース
	CommonResources* m_commonResources;

	//Rootで定義すると終了時にエラーをはく
	std::unique_ptr<ICompositeNode> m_root;
	//プレイヤ
	Player* m_player;
	//ボス敵
	BossEnemy* m_enemy;

	//実行ノードクラス
	std::unique_ptr<ExecutionNode> m_executionNode;
	//条件ノードのクラス
	std::unique_ptr<Conditions> m_conditions;
	//現在の状態
	IBehaviorNode::State m_currentState;

};

/*メモ
　毎フレーム初めからチェックする
　実行中ノードがあれば終わるまでは実行中のみ動かす
 

 改善するかもな点
 　一定のフレームごとにかえる？　毎フレームではなく
　　この時は実行中があればそれをどう実行していくかを考えなけらばならない
  実行中は毎フレーム実行中を動かしてなければ一定のフレームで更新をするでもよい

*/