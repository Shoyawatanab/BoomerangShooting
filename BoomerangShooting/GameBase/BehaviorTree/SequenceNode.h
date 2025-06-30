/*
	SequenceNode.h
	渡邊翔也
	ビヘイビアツリーのノード
	順番に子を実行する
	全ての子が実行できるとSuccess
	子が失敗したらすぐにFailureを反す
*/
#pragma once
#include "Game/Interface/ICompositeNode.h"


class CommonResources;


class SequenceNode : public ICompositeNode
{

public:
	//コンストラクタ
	SequenceNode();
	//デストラクタ
	~SequenceNode()  override;
	//初期化
	void Initialize() override;
	//更新
	IBehaviorNode::State Update(const float& deltaTime) override;

	void Finalize() override;
	//ノードの追加
	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;
private:
	//子ノード配列
	std::vector<std::unique_ptr<IBehaviorNode>> m_childNode;


};