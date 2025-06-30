#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"
#include "Game/Weapon/WeaponBase.h"


class Boomerang;
class Player;

class WeaponManager : public Actor,  public IObserver<SceneMessageType>
{
public:
	
	//特定状態のブーメラン１つをの取得
	Boomerang* GetBoomerang(WeaponBase::WeaponState getState);


public:
	//コンストラクタ
	WeaponManager(Scene* scene,Player* player);
	//デストラクタ
	~WeaponManager() override;

	// 単体更新
	void UpdateActor(const float& deltaTime) override;

	void Notify(SceneMessageType type, void*) override;

private:


private:
	//ブーメラン
	std::vector<Boomerang*> m_boomerangs;

	//手に持っているの武器
	WeaponBase* m_holdWeapon;
};

