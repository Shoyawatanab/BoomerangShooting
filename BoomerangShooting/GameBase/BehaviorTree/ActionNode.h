/*
	ActionNode.h
	渡邊翔也
	ビヘイビアツリーの実行のみのノード
	子を持たない
*/

#pragma once
#include "Game/Interface/ILeafNode.h"
#include <functional>

class CommonResources;
class ExecutionNode;
class Player;
class Enemy;

class ActionNode : public ILeafNode
{
	
public:
	//コンストラクタ
	ActionNode(std::function<IBehaviorNode::State(float)> fun);
	//デストラクタ
	~ActionNode() override;
	//初期化
	void Initialize()override;
	//更新
	IBehaviorNode::State Update(const float& deltaTime) override;

	void Finalize()override;

private:

	//関数を登録する変数
	std::function<IBehaviorNode::State(float)> m_executionNode;


};
/*メモ
  
  関数の登録変数の（float）を書いているけど登録する関数に引数がなくても正常に動いているので謎
  ()と(float)の２つを作らなきといけないと思ったけどいけてしまった
  BehaviorTreeクラスで引数が必要な関数にはstd::placeholders::_1をいている

　UpdateとRunningUpdateが中身が同じなので直したい
 　ただ実行中ノードがあるならRunningUpdateに入ってUpdateは呼ばれない
*/