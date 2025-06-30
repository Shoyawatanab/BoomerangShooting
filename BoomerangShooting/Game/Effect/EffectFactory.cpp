#include"pch.h"
#include "EffectFactory.h"
#include "Effects.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
EffectFactory::EffectFactory(Scene* scene)
	:
	Actor(scene)
	,m_explosiions{}
{

	//爆発エフェクトの作成
	for(int i = 0; i < 10; i++)
	{

		auto explosition = GetScene()->AddActor<Explosiion>(GetScene());
		m_explosiions.push_back(explosition);

	}



	for (int i = 0; i < 10; i++)
	{

		auto charge = GetScene()->AddActor<BossChargeEffect>(GetScene());

		m_chargeEffects.push_back(charge);
	}

	for (int i = 0; i < 10; i++)
	{
		auto particle = GetScene()->AddActor<Particle>(GetScene());

		m_particles.push_back(particle);

	}


	SceneMessenger::GetInstance()->Rigister({
		SceneMessageType::EXPLOSITION_EFFECT
		,SceneMessageType::CREATE_CHARGE_EFFECT
		,SceneMessageType::CREATE_PARTICLE_EFFECT
		}, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
EffectFactory::~EffectFactory()
{
}

/// <summary>
/// 通知時に呼ばれる関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void EffectFactory::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{

		case SceneMessageType::EXPLOSITION_EFFECT:
		{
			ExplosionEffectDatas data = *static_cast<ExplosionEffectDatas*>(datas);

			for (auto& explosiion : m_explosiions)
			{
				//非アクティブ状態を探す
				if (!explosiion->GetActive())
				{
					//アクティブ状態に
					explosiion->SetActive(true);
					//追加データからデータのセット
					explosiion->GetTransform()->SetScale(data.Scale);
					explosiion->GetTransform()->SetPosition(data.Position);

					break;

				}
			}

		}
			break;
		case SceneMessageType::CREATE_CHARGE_EFFECT:
		{
			CreateChargeEffectDatas data = *static_cast<CreateChargeEffectDatas*>(datas);

			for (auto& charge : m_chargeEffects)
			{
				if (!charge->GetActive())
				{

					charge->SetActive(true);
					charge->GetTransform()->SetPosition(data.Position);
					charge->GetTransform()->SetScale(data.Scale);

					break;
				}
			}

		}
			break;
		case SceneMessageType::CREATE_PARTICLE_EFFECT:
		{

			for (auto& particle : m_particles)
			{
				if (!particle->GetActive())
				{

					DirectX::SimpleMath::Vector3 position = *static_cast<DirectX::SimpleMath::Vector3*>(datas);


					particle->GetTransform()->SetPosition(position);

					particle->SetActive(true);


					break;
				}
			}

		}
			
			break;
		default:
			break;
	}

}
