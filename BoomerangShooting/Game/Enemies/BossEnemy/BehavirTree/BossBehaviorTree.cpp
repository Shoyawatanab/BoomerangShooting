#include "pch.h"
#include "BossBehaviorTree.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/BehaviorTree/BehaviorTrees.h"

#include "ExecutionNode.h"
#include "Conditions.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"



/// <summary>
/// コンストラクタ
/// </summary>
BossBehaviorTree::BossBehaviorTree(Player* player, BossEnemy* enemy)
	:
	m_commonResources{}
	,m_root{}
	,m_player{player}
	,m_enemy{enemy}
	,m_executionNode{}
	,m_conditions{}
	,m_currentState{}
{

	m_commonResources = CommonResources::GetInstance();
	m_enemy = enemy;

	m_player =player;

	//実行ノードの作成
	m_executionNode = std::make_unique<ExecutionNode>(m_player, m_enemy);
	//条件ノードの作成
	m_conditions = std::make_unique<Conditions>(m_player, m_enemy);

	//ノードツリーの作成
	CreateNodeTree();


}

/// <summary>
/// デストラクタ
/// </summary>
BossBehaviorTree::~BossBehaviorTree()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BossBehaviorTree::Update(const float& deltaTime)
{

	//実行中とそれ以外で更新処理を変える
	switch (m_currentState)
	{
		case IBehaviorNode::State::SUCCESS:
		case IBehaviorNode::State::FAILURE:
			//評価と代入
			m_currentState = m_root->Update(deltaTime);
			break;
		default:
			break;
	}

}



/// <summary>
/// ノードツリーの作成
/// </summary>
void BossBehaviorTree::CreateNodeTree()
{


	//////HP半分以下

		//ジャンプ攻撃のデコレーター
	auto jumpAttackDecorator = CreateJumpAttackDecorator();
	jumpAttackDecorator->AddNode(CreateJumpAttackActionNode());

	//振り下ろし攻撃のデコレーター
	auto closeRangeAttackDecorator = CreateCloseRangeAttackDecorator();
	//振り下ろし攻撃の追加
	closeRangeAttackDecorator->AddNode(CreateSwingDownActionNode());



	//HPが半分以下のSelector
	auto lessThanHalfHP = std::make_unique<SelectorNode>();
	//近距離攻撃の追加
	lessThanHalfHP->AddNode(std::move(closeRangeAttackDecorator));
	//ジャンプ攻撃の追加
	lessThanHalfHP->AddNode(std::move(jumpAttackDecorator));
	//歩きの追加
	lessThanHalfHP->AddNode(CreateWalkingActionNode());



	///////HP半分以上

		//遠距離攻撃のデコレーター
	auto longRangeAttackDecorator = CreateLongRangeAttackDecorator();
	//ビーム攻撃の追加
	longRangeAttackDecorator->AddNode(CreateBeamAttackActionNode());


	//振り下ろし攻撃のデコレーター
	closeRangeAttackDecorator = CreateCloseRangeAttackDecorator();
	//振り下ろし攻撃の追加
	closeRangeAttackDecorator->AddNode(CreateSwingDownActionNode());


	//HP半分以上のSelector
	auto moreThanHalfHP = std::make_unique<SelectorNode>();
	//近距離攻撃の追加
	moreThanHalfHP->AddNode(std::move(closeRangeAttackDecorator));
	//遠距離攻撃の追加
	moreThanHalfHP->AddNode(std::move(longRangeAttackDecorator));
	//歩きの追加
	moreThanHalfHP->AddNode(CreateWalkingActionNode());

	//HPが範囲内かどうかのデコレーター
	auto isMoreThanHalfHP = CreateIsHPMoreThanHalfDecorator();
	//Selectorの追加
	isMoreThanHalfHP->AddNode(std::move(moreThanHalfHP));

	///////

	auto rootSelector = std::make_unique<SelectorNode>();
	//HPが半分以上のとき
	rootSelector->AddNode(std::move(isMoreThanHalfHP));
	//HPが半分以下
	rootSelector->AddNode(std::move(lessThanHalfHP));

	//ルートの作成
	m_root = std::make_unique<Root>();
	//RootSequenceノードの追加
	m_root->AddNode(std::move(rootSelector));


	//状態の初期化
	m_currentState = IBehaviorNode::State::FAILURE;

}


/// <summary>
/// 振り下ろし攻撃のアクションノードの作成
/// </summary>
/// <returns>クラスを返す</returns>
std::unique_ptr<ActionNode> BossBehaviorTree::CreateSwingDownActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemySwingDown,m_executionNode.get()));
}

/// <summary>
/// ビーム攻撃のアクションノードの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BossBehaviorTree::CreateBeamAttackActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyBeamAction, m_executionNode.get()));
}

/// <summary>
/// 歩くアクションノードの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BossBehaviorTree::CreateWalkingActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyWalking, m_executionNode.get()));
}

/// <summary>
/// ジャンプ攻撃のアクションノードの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<ActionNode> BossBehaviorTree::CreateJumpAttackActionNode()
{
	return std::make_unique<ActionNode>(std::bind(&ExecutionNode::BossEnemyJumpAttackAction, m_executionNode.get()));
}

std::unique_ptr<DecoratorNode> BossBehaviorTree::CreateIsHPMoreThanHalfDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsHPMoreThanHalf, m_conditions.get()));
}

/// <summary>
/// 近距離攻撃範囲内かどうかのDecoratorの作成
/// </summary>
/// <returns>クラスを返す</returns>
std::unique_ptr<DecoratorNode> BossBehaviorTree::CreateCloseRangeAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInCloseRangeAttack, m_conditions.get()));
}

/// <summary>
/// 遠距離攻撃範囲内かどうかかのDecoratorの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<DecoratorNode> BossBehaviorTree::CreateLongRangeAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsInLongRangeAttack, m_conditions.get()));
}

/// <summary>
/// ジャンプ攻撃攻撃範囲内かどうかのDecoratorの作成
/// </summary>
/// <returns></returns>
std::unique_ptr<DecoratorNode> BossBehaviorTree::CreateJumpAttackDecorator()
{
	return std::make_unique<DecoratorNode>(std::bind(&Conditions::IsJumpAttackRange, m_conditions.get()));
}




