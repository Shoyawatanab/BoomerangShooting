/*
	クラス名     : PickUpManager
	説明         : 拾う動作マネージャー
	補足・注意点 :
*/
#include "pch.h"
#include "PickUpManager.h"
#include "Game/Component/PickUp/PickableComponent.h"
#include "Game/Component/PickUp/PickerComponent.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラク
/// </summary>
PickUpManager::PickUpManager()
{
}



/// <summary>
/// デストラクタ
/// </summary>
PickUpManager::~PickUpManager()
{
}



/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void PickUpManager::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	//あるリストだけ回す
	for (auto& [type, actors] : m_list)
	{
		//回収者
		auto picker = actors.first;

		//回収できない場合
		if (!picker->GetIsPickUp())
		{
			continue;
		}

		//回収対象のループ
		for (auto& pickble : actors.second)
		{
			//回収可能でないなら
			if (!pickble->GetIsPossible())
			{
				continue;
			}

			//距離を求める
			auto distance = DirectX::SimpleMath::Vector3::Distance(picker->GetActor()->GetTransform()->GetWorldPosition(), pickble->GetActor()->GetTransform()->GetWorldPosition());

			//範囲なら
			if (distance <= picker->GetPickUpRadius())
			{
				//回収可能でない状態なら
				if (!picker->GetIsRecoverable())
				{
					//回収できるようにあった時の関数
					picker->OnRecoverable();
					//状態を回収可能に
					picker->SetIsRecoverable(true);
				}
			}
			else
			{

				//回収可能状態なら
				if (picker->GetIsRecoverable())
				{
					//回収できなくなったときの関数
					picker->OnUnrecoverable();
					//状態を回収不可に
					picker->SetIsRecoverable(false);

				}

			}


		}

	}


}

/// <summary>
/// 回収の実行
/// </summary>
void PickUpManager::TryPickUp(PickerComponent* picker)
{
	
	//回収可能状態かの判定
	if (!picker->GetIsRecoverable())
	{
		return;
	}

	//タイプの取得
	auto type = picker->GetPickUpType();

	//回収対象の取得
	auto pickables = m_list[type].second;

	//一番近い回収対象の取得
	auto pickable = CheckPickUp(picker, pickables);

	//ヌルだったら
	if (!pickable)
	{
		return;
	}


	picker->OnPickUp();
	pickable->OnPickUp();
	picker->OnUnrecoverable();

}

/// <summary>
/// 回収者の追加
/// </summary>
/// <param name="type">回収タイプ</param>
/// <param name="comp">コンポーネント</param>
void PickUpManager::AddPicker(PickUpType type, PickerComponent* comp)
{
	auto& typeList = m_list[type];
	typeList.first = comp;
}

/// <summary>
/// 拾われる物の追加
/// </summary>
/// <param name="type">回収タイプ</param>
/// <param name="comp">コンポーネント</param>
void PickUpManager::AddPickable(PickUpType type, PickableComponent* comp)
{
	auto& typeList = m_list[type];
	typeList.second.push_back(comp);
}


/// <summary>
/// 回収できるか
/// </summary>
/// <param name="picker">回収者</param>
/// <param name="picktables">回収対象</param>
/// <returns>回収対象 or ヌル</returns>
PickableComponent* PickUpManager::CheckPickUp(PickerComponent* picker, std::vector<PickableComponent*> pickables)
{


	using namespace DirectX::SimpleMath;

	//回収者の座標取得
	Vector3 pickerPos = picker->GetActor()->GetTransform()->GetWorldPosition();

	//一番近い回収対象の取得
	auto it = std::min_element(pickables.begin(), pickables.end(),
		[pickerPos](PickableComponent* a, PickableComponent* b)
		{
			float distA = Vector3::Distance(pickerPos, a->GetActor()->GetTransform()->GetWorldPosition());
			float distB = Vector3::Distance(pickerPos, b->GetActor()->GetTransform()->GetWorldPosition());
			return distA < distB;
		});

	return (it != pickables.end()) ? *it : nullptr;
}


