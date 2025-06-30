#include "pch.h"
#include "ButtonComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Manager/UIManager.h"

ButtonComponent::ButtonComponent(Actor* owner)
	:
	Component(owner)
	, m_clickFunction{}
	,m_inRangeFunction{}
	,m_outOfRangeFunction{}
{

	//マネージャーに追加
	GetActor()->GetScene()->GetUIManager()->AddButtomComponent(this);

}

ButtonComponent::~ButtonComponent()
{
}

/// <summary>
/// クリック時
/// </summary>
void ButtonComponent::OnClick()
{
	//関数があれば
	if (!m_clickFunction)
	{
		return;
	}

	//登録関数の実行
	m_clickFunction();

}

/// <summary>
///　範囲内になった時の処理
/// </summary>
void ButtonComponent::InRange()
{
	//なければ
	if (!m_inRangeFunction)
	{
		return;
	}
	//関数実行
	m_inRangeFunction();
}

/// <summary>
/// 範囲外になった時関数
/// </summary>
void ButtonComponent::OutOfRange()
{
	//なければ
	if (!m_outOfRangeFunction)
	{
		return;
	}
	//関数実行
	m_outOfRangeFunction();
}
