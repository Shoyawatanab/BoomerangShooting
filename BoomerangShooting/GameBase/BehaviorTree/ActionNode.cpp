#include "pch.h"
#include "ActionNode.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="fun">登録する関数</param>
ActionNode::ActionNode(std::function<IBehaviorNode::State(float)> fun)
	:
	m_executionNode{}
{

	assert(fun);

	//関数の登録
	m_executionNode = fun;


}

/// <summary>
///デストラクタ
/// </summary>
ActionNode::~ActionNode()
{

}

/// <summary>
/// 初期化
/// </summary>
void ActionNode::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>関数の実行結果</returns>
IBehaviorNode::State ActionNode::Update(const float& deltaTime)
{

	return m_executionNode(deltaTime);
}





void ActionNode::Finalize()
{
}



