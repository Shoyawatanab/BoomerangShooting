#include "pch.h"
#include "SelectorNode.h"


/// <summary>
/// コンストラクタ
/// </summary>
SelectorNode::SelectorNode()
	:
	m_childNode{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
SelectorNode::~SelectorNode()
{

}

/// <summary>
/// 初期化
/// </summary>
void SelectorNode::Initialize()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State SelectorNode::Update(const float& deltaTime)
{
	for (auto& node : m_childNode)
	{
		
		switch (node->Update(deltaTime))
		{
			
			case IBehaviorNode::State::SUCCESS:
				//成功を返す
				return State::SUCCESS;
			case IBehaviorNode::State::FAILURE:
				//他の子ノードがせいこうするかもしれないから何も返さず継続する
				break;
			default:
				break;
		}

	}
	
	//１つも成功しなかったら
	return State::FAILURE;

}




void SelectorNode::Finalize()
{
}

/// <summary>
/// 子ノードの追加
/// </summary>
/// <param name="node">子ノード</param>
void SelectorNode::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	//初期化
	node->Initialize();
	//追加
	m_childNode.emplace_back(std::move(node));

}


