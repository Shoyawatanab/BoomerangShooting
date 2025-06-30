#include "pch.h"
#include "SequenceNode.h"


/// <summary>
/// コンストラクタ
/// </summary>
SequenceNode::SequenceNode()
	:
	m_childNode{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
SequenceNode::~SequenceNode()
{

}

/// <summary>
/// 初期化
/// </summary>
void SequenceNode::Initialize()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State SequenceNode::Update(const float& deltaTime)
{

	for (auto& node : m_childNode)
	{

		switch (node->Update(deltaTime))
		{

			case IBehaviorNode::State::SUCCESS:
				break;
			case IBehaviorNode::State::FAILURE:
				return State::FAILURE;
			default:
				break;
		}

	}

	//すべて成功したら
	return State::SUCCESS;
}




void SequenceNode::Finalize()
{
}

/// <summary>
/// 子ノードの追加
/// </summary>
/// <param name="node">子ノード</param>
void SequenceNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	//初期化
	node->Initialize();
	//追加
	m_childNode.emplace_back(std::move(node));

}


