/*
	クラス名     : ActionController
	説明         : アクションマネージャーの基底クラス　今回はボス敵で使用
	補足・注意点 :
*/
#pragma once

class ActionController;

class ActionManager
{
public:
	//コンストラクタ
	ActionManager();
	//デストラクタ
	virtual ~ActionManager() = 0;
	//更新処理 true:実行終了   false:実行中
	bool Update(const float& deltaTime);

	void SetStartAction(const std::string& name);

	//行動の変更
	void ChangeAction(const std::string& actionName);
	//行動の追加
	void AddAction(const std::string& name, std::unique_ptr<ActionController> action);

	//行動の中止
	void ActionCancel();

private:
	//実行アクション
	std::pair<std::string, ActionController*> m_action;
	//アクションの保存変数
	std::unordered_map<std::string, std::unique_ptr<ActionController>> m_actionList;


};