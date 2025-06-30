#include "pch.h"
#include "AnimationController.h"
#include "GameBase/Animation/Animator.h"

/// <summary>
/// コンストラクタ
/// </summary>
AnimationController::AnimationController()
	:
	m_animations{}
	,m_currentAnimation{}
	,m_normalAnimation{}
	,m_stateTransitionList{}
	,m_state{ ExecutionState::NONE}
	,m_triggerTransitionList{}
	,m_floatTransitionList{}
	,m_transitionParamter{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
AnimationController::~AnimationController()
{
	m_animations.clear();
	m_stateTransitionList.clear();
	m_triggerTransitionList.clear();
	m_floatTransitionList.clear();
	m_transitionParamter.clear();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void AnimationController::Update(const float& deltaTime)
{

	//再生状態でない場合
	if (m_state == ExecutionState::NONE)
	{
		return;
	}

	//アニメーションの再生状態
	if (!m_currentAnimation->Update(deltaTime))
	{
		//再生中
		return;
	}


	switch (m_state)
	{
		case AnimationController::ExecutionState::NONE:
			break;
		case AnimationController::ExecutionState::PLAY:

			//ループ再生かどうか
			if (m_currentAnimation->GetIsLoop())
			{
				m_currentAnimation->Rerun();
			}
			//ループでないとき
			else
			{
				m_state = ExecutionState::NONE;

			}
			break;
		case AnimationController::ExecutionState::TRIIGER:
		case AnimationController::ExecutionState::FLOAT:
			//通常アニメーションにもどす
			ChangeAnimation(m_normalAnimation);
			//状態の変更
			m_state = ExecutionState::PLAY;
			break;
		default:
			break;
	}



}




/// <summary>
/// アニメーションの追加
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="animationName">アニメーション名</param>
/// <param name="filePath">ファイルパス</param>
/// <param name="actors">アニメーションオブジェクト</param>
/// <param name="isNormal">初期アニメーションか</param>
void AnimationController::AddAnimatoin(Actor* owner, std::string animationName, std::string filePath, std::vector<std::pair<std::string, Actor*>> actors, bool isNormal)
{

	//既に存在するか探す
	auto it = m_animations.find(animationName);

	//すでにあれば
	if (it != m_animations.end())
	{
		return;
	}
	//アニメターの作成
	auto animator = std::make_unique<Animator>(owner, animationName, filePath, actors);

	//追加
	m_animations[animationName] = std::move(animator);


	//通常アニメーションなら
	if (isNormal)
	{
		//通常アニメーションとして保持
		m_normalAnimation = m_animations[animationName].get();
		//実行アニメーションに
		m_currentAnimation = m_animations[animationName].get();
		m_state = ExecutionState::PLAY;
	}

}

/// <summary>
/// トリガー状態遷移フローの作成
/// </summary>
/// <param name="fromAnimationName">遷移元アニメーション名</param>
/// <param name="toAnimationName">遷移先アニメーション名</param>
/// <param name="name">遷移名</param>
void AnimationController::CreateTriggerTransition(const std::string& fromAnimationName, const std::string& toAnimationName, const std::string& connectionName)
{

	//なければ
	if (!IsFindParameter(connectionName))
	{
		return;
	}

	//トリガーリストから探す
	auto it = m_triggerTransitionList.find(connectionName);

	//あれば
	if (it != m_triggerTransitionList.end())
	{
		return;
	}

	//リストに追加
	m_triggerTransitionList[connectionName] = { fromAnimationName,toAnimationName };

}

/// <summary>
/// Float状態遷移フローの作成
/// </summary>
/// <param name="fromAnimationName">遷移元アニメーション名</param>
/// <param name="toAnimationName">遷移先アニメーション名</param>
/// <param name="name">遷移名</param>
/// <param name="value">基準値</param>
void AnimationController::CreateFloatTransition(const std::string& fromAnimationName, const std::string& toAnimationName, const std::string& connectionName, const float& value, FloatState state)
{

	//なければ
	if (!IsFindParameter(connectionName))
	{
		return;
	}

	//トリガーリストから探す
	auto it = m_floatTransitionList.find(connectionName);

	//あれば
	if (it != m_floatTransitionList.end())
	{
		return;
	}

	//リストに追加
	m_floatTransitionList[connectionName] = { fromAnimationName,toAnimationName,state,value };

}

/// <summary>
/// AnyStateからのトリガー状態遷移フローの作成 
/// </summary>
/// <param name="toAnimationName">遷移先アニメーション名</param>
/// <param name="name">遷移名</param>
void AnimationController::CreateAnyStateToTriggerTransition(const std::string& toAnimationName, const std::string& connectionName)
{
	//なければ
	if(!IsFindParameter(connectionName))
	{
		return;
	}

	//トリガーリストから探す
	auto it = m_triggerTransitionList.find(connectionName);

	//あれば
	if (it != m_triggerTransitionList.end())
	{
		return;
	}

	//リストに追加
	m_triggerTransitionList[connectionName] = { "AnyState",toAnimationName };

}

/// <summary>
/// AnyStateからのFloat状態遷移フローの作成
/// </summary>
/// <param name="toAnimationName">遷移先アニメーション名</param>
/// <param name="name">遷移名</param>
/// <param name="value">基準値</param>
void AnimationController::CreateAnyStateToFloatTransition(const std::string& toAnimationName, const std::string& connectionName, const float& value, FloatState state)
{
	//なければ
	if (!IsFindParameter(connectionName))
	{
		return;
	}

	//トリガーリストから探す
	auto it = m_floatTransitionList.find(connectionName);

	//あれば
	if (it != m_floatTransitionList.end())
	{
		return;
	}

	//リストに追加
	m_floatTransitionList[connectionName] = { "AnyState",toAnimationName,state,value };
}



/// <summary>
/// アニメーションの再生
/// </summary>
/// <param name="animatioName">アニメーション名</param>
void AnimationController::Play(const std::string& animationName)
{
	//切り替え判定
	if (!IsChangeAnimation(animationName))
	{
		return;
	}

	//様態の変更
	m_state = ExecutionState::PLAY;
	//実行アニメーションの変更
	ChangeAnimation(m_animations[animationName].get());
}

/// <summary>
/// アニメーションの切り替え　1回だけ実行
/// </summary>
/// <param name="connectionName">状態接続名</param>
void AnimationController::SetTrigger(const std::string& connectionName)
{
	//パラメーターになければ
	if (!IsFindParameter(connectionName))
	{
		return;
	}

	//実行できるか
	if (!CheckTrigger(connectionName))
	{
		//できない
		return;
	}

	//様態の変更
	m_state = ExecutionState::TRIIGER;
	//実行アニメーションの変更
	ChangeAnimation(m_animations[m_triggerTransitionList[connectionName].second].get());

}

/// <summary>
/// アニメーションの切り替え
/// </summary>
/// <param name="connectionName">状態接続名</param>
/// <param name="value">比較値</param>
void AnimationController::SetFloat(const std::string& connectionName, const float& value)
{
	//トリガー状態ならやらない
	if (m_state == ExecutionState::TRIIGER)
	{
		return;
	}

	//パラメーターになければ
	if (!IsFindParameter(connectionName))
	{
		return;
	}
	//探す
	auto it = m_floatTransitionList.find(connectionName);
	//リストに泣ければ
	if (it == m_floatTransitionList.end())
	{
		return;
	}


	//Anystateかどうか
	if (it->second.FromName == "AnyState" ||                                   //AnyStateかどうか
		m_currentAnimation->GetAnimaiionName() == it->second.FromName)		   //遷移元のアニメーションと実行アニメーションが同じか
	{
		if (CheckFloatValue(connectionName, value))
		{
			//様態の変更
			m_state = ExecutionState::FLOAT;
			//実行アニメーションの変更
			ChangeAnimation(m_animations[m_floatTransitionList[connectionName].ToName].get());
			return;
		}
	}



	//すでにアニメーションに切り替わっている場合
	if (m_currentAnimation->GetAnimaiionName() == it->second.ToName)
	{
		if (!CheckFloatValue(connectionName, value))
		{
			//様態の変更
			m_state = ExecutionState::PLAY;
			//実行アニメーションの変更
			ChangeAnimation(m_normalAnimation);

		}

	}


}



/// <summary>
/// 状態遷移リストに追加
/// </summary>
/// <param name="state1">状態１</param>
/// <param name="state2">状態２</param>
void AnimationController::AddTransitionList(std::string state1, std::string state2)
{
	
	; auto& it = m_stateTransitionList[state1];

	// すでに string2 が登録されているかチェック
	if (std::find(it.begin(), it.end(), state2) == it.end())
	{
		// 登録されていなければ追加
		it.push_back(state2); 
	}

}

/// <summary>
/// アニメーションの切り替えを行ってもよいか
/// </summary>
/// <param name="animationName">アニメーション名</param>
/// <returns>　true: よい  false:ダメ</returns>
bool AnimationController::IsChangeAnimation(const std::string& animationName)
{
	//探す
	auto it = m_animations.find(animationName);

	//なければ
	if (it == m_animations.end())
	{
		return false;
	}
	//実行中と同じなら
	if (m_currentAnimation == m_animations[animationName].get())
	{
		return false ;
	}


	return true;
}

/// <summary>
/// 遷移名があるか
/// </summary>
/// <param name="connectionName">遷移名</param>
/// <returns>true:あり    false:なし</returns>
bool AnimationController::IsFindParameter(const std::string& connectionName)
{

	auto it = m_transitionParamter.find(connectionName);

	//なければ
	if (it == m_transitionParamter.end())
	{
		//なし
		return false;
	}
	//あり
	return true;
}

/// <summary>
/// トリガーの実行ができるかの判定
/// </summary>
/// <param name="connectionName">遷移名</param>
/// <returns>true:できる   false:できない</returns>
bool AnimationController::CheckTrigger(const std::string& connectionName)
{
	
	auto it = m_triggerTransitionList.find(connectionName);
	//リストに泣ければ
	if (it == m_triggerTransitionList.end())
	{
		return false;
	}

	//Anystateかどうか
	if (it->second.first == "AnyState")
	{
		//できる
		return true;
	}

	//実行中アニメーションと遷移元アニメーション名が一致するか
	if (m_currentAnimation->GetAnimaiionName() == it->second.first)
	{
		//しない場合
		return true;
	}


	return false;
}

/// <summary>
/// Floatの遷移フローがあるかの判定
/// </summary>
/// <param name="connectionName">遷移名</param>
/// <returns>true:できる   false:できない</returns>
bool AnimationController::CheckFloatTransition(const std::string& connectionName, const float& value)
{
	auto it = m_floatTransitionList.find(connectionName);
	//リストに泣ければ
	if (it == m_floatTransitionList.end())
	{
		return false;
	}



	//Anystateかどうか
	if (it->second.FromName == "AnyState")
	{
		//できる
		return true;
	}


	//実行中アニメーションと遷移元アニメーション名が一致するか
	if (m_currentAnimation->GetAnimaiionName() == it->second.FromName)
	{
		//できる
		return true;
	}



	//できない
	return false;
}

/// <summary>
/// Floatの値による比較
/// </summary>
/// <param name="connectionName">遷移名</param>
/// <param name="value">値</param>
/// <returns>true: できる  false:できない</returns>
bool AnimationController::CheckFloatValue(const std::string& connectionName, const float& value)
{
	//値の比較
	switch (m_floatTransitionList[connectionName].State)
	{
		//大きい
		case FloatState::Greater:
			if (value > m_floatTransitionList[connectionName].Value)
			{
				//できる
				return true;
			}
			break;
			//小さい
		case FloatState::Less:
			if (value <= m_floatTransitionList[connectionName].Value)
			{
				//できる
				return true;
			}
			break;
		default:
			break;
	}

	return false;
}


/// <summary>
/// アニメーションの切り替え
/// </summary>
/// <param name="animatior">次のアニメーション</param>
void AnimationController::ChangeAnimation(Animator* animatior)
{
	//同じなら行わない
	if (m_currentAnimation == animatior)
	{
		if(!m_currentAnimation->GetIsEnd())
		{
			m_currentAnimation->Rerun();
		}

		return;
	}
	//初期化
	m_currentAnimation->Rerun();
	//切り替え
	m_currentAnimation = animatior;

}
