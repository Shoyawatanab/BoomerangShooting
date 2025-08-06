/*
	クラス名     : BossEnemyLeftArm
	説明         : ボス敵の左腕モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"

BossEnemyLeftArm::BossEnemyLeftArm(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyArm"
		, Params::BOSSENEMY_LEFTARM_HP
		, Params::BOSSENEMY_LEFTARM_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTARM_SPHERE_COLLIDER_SIZE
		,boss)
{


	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_LEFTARM_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTARM_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTARM_ROTATION);

	//以下追加部位の作成


	//爆発音の作成
	m_hitSE = AddComponent<SoundComponent>(this, "AttackHit", SoundComponent::SoundType::SE);


}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyLeftArm::~BossEnemyLeftArm()
{
}

/// <summary>
/// 個別の当たった時の関数
/// </summary>
/// <param name="collider"></param>
void BossEnemyLeftArm::OnCollisionEnterActor(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:

			//SwingDown状態なら
			if (GetBossEnemy()->GetCurrentActionType() == BossEnemy::ActionType::SWINGDOWN)
			{

				DirectX::SimpleMath::Vector3 position = GetTransform()->GetWorldPosition();

				position.y = 0.1f;
				//パーティクル作成
				Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::CREATE_PARTICLE_EFFECT, &position);
				//サウンド再生
				m_hitSE->Play();

			}
		
		
			break;
		default:
			break;
	}

}
