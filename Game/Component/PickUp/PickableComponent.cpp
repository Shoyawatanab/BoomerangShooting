/*
	クラス名    : PickableComponent
	説明        : 拾われる側コンポーネント
	補足・注意点:
*/
#include "pch.h"
#include "PickableComponent.h"
#include "Game/Manager/PickUp/PickUpManager.h"
#include "Game/Scene/PlayScene.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="type">回収タイプ</param>
PickableComponent ::PickableComponent (Actor* owner, PickUpManager::PickUpType type)
	:
	Component(owner)
	,m_isPossible{false}
{

	//現在のシーンをプレイシーンにキャスト
	auto playScene = static_cast<PlayScene*>(GetActor()->GetScene());
	//プレイシーンのマネージャーに拾われる側として登録
	playScene->GetPickUpManager()->AddPickable(type, this);


}

/// <summary>
/// デストラクタ
/// </summary>
PickableComponent ::~PickableComponent ()
{
}

/// <summary>
/// 回収時
/// </summary>
void PickableComponent::OnPickUp()
{
	//登録されていなければ
	if (!m_onPickUp)
	{
		return;
	}

	//関数実行
	m_onPickUp();

}

/// <summary>
/// 回収できるようになったとき
/// </summary>
void PickableComponent::OnRecoverable()
{

	//なければ
	if(!m_recoverable)
	{
		return;
	}

	//関数実行
	m_recoverable();

}

/// <summary>
/// 回収できなくなったとき
/// </summary>
void PickableComponent::OnUnrecoverable()
{

	//なければ
	if (!m_unrecoverable)
	{
		return;
	}

	//関数実行
	m_unrecoverable;

}
