#include "pch.h"
#include "BoomerangStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStates.h"
#include "Game/Weapon/Boomerang/Boomerang.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="boomerang">ブーメラン</param>
BoomerangStateMachine::BoomerangStateMachine(Boomerang* boomerang, Player* player)
	:
	m_boomerang{boomerang}
{

	//IDLE
	AddState(BoomerangState::IDEL, std::make_unique<BoomerangIdle>(this, boomerang,player));
	AddState(BoomerangState::THROW, std::make_unique<BoomerangThrow>(this, boomerang,player));
	AddState(BoomerangState::GET_READY, std::make_unique<BoomerangGetReady>(this, boomerang,player));

	//初期状態
	SetStartState(BoomerangState::IDEL);
	




}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangStateMachine::~BoomerangStateMachine()
{
}


/// <summary>
/// 派生先のChangeState時の処理
/// </summary>
/// <param name="state"></param>
void BoomerangStateMachine::DerivationChangeState(BoomerangState state)
{
	switch (state)
	{
		case BoomerangState::IDEL:
			m_boomerang->SetWeaponState(WeaponBase::WeaponState::BOOMERANG_IDLE);
			break;
		case BoomerangState::THROW:
			m_boomerang->SetWeaponState(WeaponBase::WeaponState::BOOMERANG_THROW);
			break;
		case BoomerangState::GET_READY:
			m_boomerang->SetWeaponState(WeaponBase::WeaponState::BOOMERANG_GET_READY);

			break;
		default:
			break;
	}
}

///// <summary>
///// 通知時に呼び出される関数
///// </summary>
///// <param name="type"></param>
///// <param name="datas"></param>
//void BoomerangStateMachine::Notify(MessageType type, void* datas)
//{
//	
//	switch (type)
//	{
//		case MessageType::BOOMERANG_IDEL_STATE:
//			ChangeState(BoomerangState::IDEL);
//			break;
//		case MessageType::BOOMERANG_GET_READY_STATE:
//			ChangeState(BoomerangState::GET_READY);
//			break;
//		case MessageType::BOOMERANG_THROW_STATE:
//			ChangeState(BoomerangState::THROW);
//			break;
//		default:
//			break;
//	}
//	
//}
