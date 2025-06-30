#include "pch.h"
#include "WeaponManager.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Messenger/Scene/SceneMessages.h"



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

	//メッセンジャーに登録
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOOMERANG_IDEL_STATE
			,SceneMessageType::BOOMERANG_GET_READY_STATE
			,SceneMessageType::BOOMERANG_THROW_STATE
		}
		, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
WeaponManager::~WeaponManager()
{
}

/// <summary>
/// 単体更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void WeaponManager::UpdateActor(const float& deltaTime)
{

}

/// <summary>
/// 通知時に呼び出される関数
/// </summary>
/// <param name="type"></param>
/// <param name="datas"></param>
void WeaponManager::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{
		case SceneMessageType::BOOMERANG_IDEL_STATE:
			//手に持っていたら　　構えているときのIDEL変更
			if (m_holdWeapon)
			{
				//状態の変更
				m_holdWeapon->ChangeState(WeaponBase::WeaponState::BOOMERANG_IDLE);
				m_holdWeapon = nullptr;
			}
			break;
		case SceneMessageType::BOOMERANG_GET_READY_STATE:
			//通常状態のブーメランを探す
			m_holdWeapon = GetBoomerang(WeaponBase::WeaponState::BOOMERANG_IDLE);
			//ヌルでない場合
			if (m_holdWeapon)
			{
				//状態の変更
				m_holdWeapon->ChangeState(WeaponBase::WeaponState::BOOMERANG_GET_READY);
			}
			break;
		case SceneMessageType::BOOMERANG_THROW_STATE:
			//構えている場合
			if (!m_holdWeapon) { return; }
			//状態の変更
			m_holdWeapon->ChangeState(WeaponBase::WeaponState::BOOMERANG_THROW);
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
Boomerang* WeaponManager::GetBoomerang(WeaponBase::WeaponState getState)
{

	for (auto& boomerang : m_boomerangs)
	{
		if (boomerang->GetWeaponState() == getState)
		{
			return boomerang;
		}
	}

	return nullptr;
}
