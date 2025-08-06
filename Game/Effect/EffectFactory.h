/*
	クラス名     : EffectFactory
	説明         : エフェクトの作成・管理を行うクラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Explosiion;
class BossChargeEffect;
class Particle;

class EffectFactory : public Actor
{
public:
	//コンストラク
	EffectFactory(Scene* scene);
	//デストラクタ
	~EffectFactory() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:
	//爆発エフェクト
	std::vector<Explosiion*> m_explosiions;
	//ジャージエフェクト
	std::vector<BossChargeEffect*> m_chargeEffects;
	//パーティクルエフェクト
	std::vector<Particle*> m_particles;

};