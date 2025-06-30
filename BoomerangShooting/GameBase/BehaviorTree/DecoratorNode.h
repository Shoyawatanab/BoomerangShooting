/*
	DecoratorNode.h
	渡邊翔也
	ビヘイビアツリーの条件判定のノード
	条件を通れば子のステートを返す
	　　　通らなければFailureを返す
*/
#pragma once
#include "Game/Interface/ICompositeNode.h"

class CommonResources;


class DecoratorNode : public ICompositeNode
{

public:
	//コンストラクタ
	DecoratorNode(std::function<bool(float)> fun);
	//デストラクタ
	~DecoratorNode() override;
	//初期化
	void Initialize() override;
	//更新
	IBehaviorNode::State Update(const float& deltaTime) override;

	void Finalize() override ;
	//子ノードの実行
	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;

private:

	//子ノード配列
	std::unique_ptr<IBehaviorNode> m_childNode;


	//関数を登録する変数
	std::function<bool(float)> m_condition;


}; 

/*メモ
　UpdateとRunningUpdateが中身が同じなので直したい
 　ただ実行中ノードがあるならRunningUpdateに入ってUpdateは呼ばれない
*/