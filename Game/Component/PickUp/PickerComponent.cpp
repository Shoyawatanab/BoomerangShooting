/*
	クラス名    : PickerComponent
	説明        : 拾う側コンポーネント
	補足・注意点:　このゲームオリジナルコンポーネント
	　　　　　　　プレイシーンにマネージャーがある
*/
#include "pch.h"
#include "PickerComponent.h"
#include "Game/Manager/PickUp/PickUpManager.h"
#include "Game/Scene/PlayScene.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="type">回収タイプ</param>
/// <param name="pickUpRadius">回収範囲</param>
PickerComponent::PickerComponent(Actor* owner, PickUpManager::PickUpType type, float pickUpRadius)
	:
	Component(owner)
	,m_pickUpRadius{pickUpRadius}
	,m_isPickUp{false}
	,m_isRecoverable{false}
	,m_type{type}
{

	//現在のシーンをプレイシーンにキャスト
	auto playScene = static_cast<PlayScene*>(GetActor()->GetScene());
	
	//プレイシーンからマネージャーの取得
	m_manger = playScene->GetPickUpManager();
	m_manger->AddPicker(type, this);

}

/// <summary>
/// デストラクタ
/// </summary>
PickerComponent::~PickerComponent()
{

}

/// <summary>
/// 回収の実行
/// </summary>
void PickerComponent::TryPickUp()
{
	m_manger->TryPickUp(this);
}

/// <summary>
/// 回収時
/// </summary>
void PickerComponent::OnPickUp()
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
void PickerComponent::OnRecoverable()
{
	//なければ
	if (!m_recoverable)
	{
		return;
	}

	//関数実行
	m_recoverable();
}

/// <summary>
/// 回収できなくなったとき
/// </summary>
void PickerComponent::OnUnrecoverable()
{
	//なければ
	if (!m_unrecoverable)
	{
		return;
	}

	//関数実行
	m_unrecoverable();
}
