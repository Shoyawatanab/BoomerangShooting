/*
複数のアニメーターを管理するクラス
*/
#pragma once
#include <unordered_map>

class Animator;
class Actor;

class AnimationController
{
public:
	//アニメーションの実行状態
	enum class ExecutionState
	{
		NONE        
		,PLAY       //通常再生
		,TRIIGER	//１回だけ実行
		,FLOAT		//
	};

	//状態遷移のフロー
	enum class TransitionState
	{
		UNIDIRECTIONAL       //片方向
		, BIDIRECTIONAL      //双方向
	};

	enum  class FloatState
	{
		Greater   //大きい
		,Less	  //小さい
	};



	struct FloatParameter
	{
		std::string  FromName;
		std::string  ToName;
		FloatState   State;
		float        Value;
	};

public:
	//コンストラクタ
	AnimationController();
	//デストラクタ
	virtual ~AnimationController();
	//更新処理
	void Update(const float& deltaTime);

	//アニメーションの追加
	void AddAnimatoin(Actor* owner,std::string animationName, std::string filePath,std::vector<std::pair<std::string,Actor*>>, bool isNormal = false);
	//トリガー状態遷移フローの作成
	void CreateTriggerTransition(const std::string& fromAnimationName,const std::string& toAnimationName , const std::string& connectionName);
	//Float状態遷移フローの作成
	void CreateFloatTransition(const std::string& fromAnimationName, const std::string& toAnimationName, const std::string& connectionName,const float& value, FloatState state);
	//AnyStateからのトリガー状態遷移フローの作成 
	void CreateAnyStateToTriggerTransition(const std::string& toAnimationName, const std::string& connectionName);
	//AnyStateからのFloat状態遷移フローの作成
	void CreateAnyStateToFloatTransition(const std::string& toAnimationName, const std::string& connectionName, const float& value, FloatState state);
	//遷移パラメーターの作成    状態遷移名　状態
	void CrateTransitionParameter(std::unordered_map<std::string, ExecutionState> parameters) { m_transitionParamter = parameters; };

	//アニメーションの再生　　終了後Loop出ないなら止まる
	void Play(const std::string& animationName);
	//アニメーションの切り替え　終了後通常に戻る
	void SetTrigger(const std::string& connectionName);
	//アニメーションの切り替え　対よりも大きい場合のみ変更　
	void SetFloat(const std::string& connectionName,const float& value);

private:

	//状態遷移リストに追加
	void AddTransitionList(std::string state1, std::string state2);
	//アニメーションの切り替えを行ってもいいか　true: よい  false:ダメ
	bool IsChangeAnimation(const std::string& animationName);
	//遷移名がパラメーターにあるか
	bool IsFindParameter(const std::string& connectionName);
	//トリガーの実行ができるかの判定
	bool CheckTrigger(const std::string& connectionName);
	//Floatの遷移フローがあるかの判定
	bool CheckFloatTransition(const std::string& connectionName,const float& value);
	//Floatの値による判定
	bool CheckFloatValue(const std::string& connectionName,const float& value);

	//アニメーションの切り替え
	void ChangeAnimation(Animator* animatior);
private:

	//実行アニメーション
	Animator* m_currentAnimation;
	//通常アニメーション
	Animator* m_normalAnimation;
	//アニメーションの格納変数
	std::unordered_map<std::string , std::unique_ptr<Animator>> m_animations;

	//状態遷移の保存
	std::unordered_map<std::string,std::vector<std::string>> m_stateTransitionList;

	//実行状態
	ExecutionState m_state;
	//遷移パラメーター
	std::unordered_map<std::string, ExecutionState> m_transitionParamter;
	//トリガー遷移リスト
	std::unordered_map<std::string, std::pair<std::string, std::string>> m_triggerTransitionList;
	//フロート遷移リスト
	std::unordered_map<std::string, FloatParameter> m_floatTransitionList;

};