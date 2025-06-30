#include "pch.h"
#include "AnimatorComponent.h"
#include "GameBase/Animation/AnimationController.h"


AnimatorComponent::AnimatorComponent(Actor* owner, std::unique_ptr<AnimationController> controller)
	:
	Component(owner)
	,m_controller{std::move(controller)}
{
}

/// <summary>
/// デストラクタ
/// </summary>
AnimatorComponent::~AnimatorComponent()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void AnimatorComponent::Update(const float& deltaTime)
{
	m_controller->Update(deltaTime);
}

/// <summary>
/// アニメーションの再生
/// </summary>
/// <param name="animatioName">アニメーション名</param>
void AnimatorComponent::Play(const std::string& animatioName)
{
	m_controller->Play(animatioName);
}


/// <summary>
/// アニメーションを1回実行
/// </summary>
/// <param name="connectionName">状態接続名</param>
void AnimatorComponent::SetTrigger(const std::string& connectionName)
{
	m_controller->SetTrigger(connectionName);
}

/// <summary>
/// 値が設定値よりも大きければアニメーションを再生
/// </summary>
/// <param name="connectionName">状態接続名名</param>
/// <param name="value">値</param>
void AnimatorComponent::SetFloat(const std::string& connectionName, const float& value)
{
	m_controller->SetFloat(connectionName, value);
}



