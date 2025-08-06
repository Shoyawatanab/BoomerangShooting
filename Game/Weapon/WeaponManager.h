/*
	クラス名     : WeaponManager
	説明         : 武器のマネージャー
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Weapon/WeaponBase.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Messenger/Messengers.h"


class Boomerang;
class Player;

class WeaponManager : public Actor
{
public:
	
	//特定状態のブーメラン１つをの取得
	Boomerang* GetBoomerang(BoomerangState getState);


public:
	//コンストラクタ
	WeaponManager(Scene* scene,Player* player);
	//デストラクタ
	~WeaponManager() override;


	void Notify(SceneMessageType type, void*);

private:



private:
	//ブーメラン
	std::vector<Boomerang*> m_boomerangs;

	//手に持っているの武器
	WeaponBase<BoomerangState>* m_holdWeapon;

};

