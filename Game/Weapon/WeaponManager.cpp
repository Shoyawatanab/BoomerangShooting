/*
	クラス名     : WeaponManager
	説明         : 武器のマネージャー
	補足・注意点 :
*/
#include "pch.h"
#include "WeaponManager.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"


WeaponManager::WeaponManager(Scene* scene, Player* player)
	:
	Actor(scene)
	,m_boomerangs{}
	, m_holdWeapon{}
{

	//ブーメランを作成
	for (int i = 0; i < 3; i++)
	{
		auto boomerang = GetScene()->AddActor<Boomerang>(scene, player);
		m_boomerangs.push_back(boomerang);
	}

	//通知を受け取るコンポーネントの追加
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::BOOMERANG_IDEL_STATE
			,SceneMessageType::BOOMERANG_GET_READY_STATE
			,SceneMessageType::BOOMERANG_THROW_STATE
		}
		, std::bind(&WeaponManager::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);


}

/// <summary>
/// デストラクタ
/// </summary>
WeaponManager::~WeaponManager()
{
}



/// <summary>
/// 通知時に呼び出される関数
/// </summary>
/// <param name="type"></param>
/// <param name="datas"></param>
void WeaponManager::Notify(SceneMessageType type, void* datas)
{

	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::BOOMERANG_IDEL_STATE:
			//手に持っていたら　　構えているときのIDEL変更
			if (m_holdWeapon)
			{
				//状態の変更
				m_holdWeapon->ChangeState(BoomerangState::IDEL);
				m_holdWeapon = nullptr;
			}
			break;
		case SceneMessageType::BOOMERANG_GET_READY_STATE:
			//通常状態のブーメランを探す
			m_holdWeapon = GetBoomerang(BoomerangState::IDEL);
			//ヌルでない場合
			if(m_holdWeapon)
			{
				//状態の変更
				m_holdWeapon->ChangeState(BoomerangState::GET_READY);
			}
			break;
		case SceneMessageType::BOOMERANG_THROW_STATE:
			//構えている場合
			if (!m_holdWeapon) { return; }
			//状態の変更
			m_holdWeapon->ChangeState(BoomerangState::THROW);
			m_holdWeapon = nullptr;
			break;
		default:
			break;
	}

}

/// <summary>
/// 特定状態のブーメラン１つをの取得
/// </summary>
/// <param name="getState">欲しい状態</param>
/// <returns>ブーメランクラス</returns>
Boomerang* WeaponManager::GetBoomerang(BoomerangState getState)
{

	for (auto& boomerang : m_boomerangs)
	{
		if (boomerang->GetState() == getState)
		{
			return boomerang;
		}
	}

	return nullptr;
}
