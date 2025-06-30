#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Explosiion;
class BossChargeEffect;
class Particle;

class EffectFactory : public Actor , public IObserver<SceneMessageType>
{
public:
	//コンストラク
	EffectFactory(Scene* scene);
	//デストラクタ
	~EffectFactory() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas)  override;


private:
	//爆発エフェクト
	std::vector<Explosiion*> m_explosiions;
	//ジャージエフェクト
	std::vector<BossChargeEffect*> m_chargeEffects;
	//パーティクルエフェクト
	std::vector<Particle*> m_particles;

};