/*
	クラス名     : Root
	説明         : ビヘイビアツリーのルートノード
	補足・注意点 :　順番に子を実行する。全ての子が実行できるとSuccess、子が失敗したらすぐにFailureを反す
*/
#include "pch.h"
#include "Root.h"


/// <summary>
/// コンストラクタ
/// </summary>
Root::Root()
	:
	m_childNode{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
Root::~Root()
{
	Finalize();
}

/// <summary>
/// 初期化
/// </summary>
void Root::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State Root::Update(const float& deltaTime)
{
	//子ノードの実行
	return 	m_childNode->Update(deltaTime);

}




void Root::Finalize()
{
}

/// <summary>
/// 必要なノードの追加
/// </summary>
/// <param name="node">子ノード</param>
void Root::AddNode(std::unique_ptr<IBehaviorNode> node)
{
	node->Initialize();

	m_childNode = std::move(node);

}


