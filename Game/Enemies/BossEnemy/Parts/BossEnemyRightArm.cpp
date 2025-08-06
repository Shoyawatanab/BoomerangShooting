/*
	クラス名     : BossEnemyRightArm
	説明         : ボス敵の右腕モデル
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyRightArm.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"

BossEnemyRightArm::BossEnemyRightArm(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene
		, PARTS_NAME
		, "BossEnemyArm"
		, Params::BOSSENEMY_RIGHTARM_HP
		, Params::BOSSENEMY_RIGHTARM_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_RIGHTARM_SPHERE_COLLIDER_SIZE
		, boss)
{



	//位置情報
	GetTransform()->Translate(Params::BOSSENEMY_RIGHTARM_POSITION);
	//大きさ
	GetTransform()->SetScale(Params::BOSSENEMY_RIGHTARM_SCALE);
	//回転
	GetTransform()->SetRotate(Params::BOSSENEMY_RIGHTARM_ROTATION);

	//爆発音の作成
	m_hitSE = AddComponent<SoundComponent>(this, "AttackHit", SoundComponent::SoundType::SE);


}

/// <summary>
///　デストラクタ
/// </summary>
BossEnemyRightArm::~BossEnemyRightArm()
{
}


/// <summary>
/// 個別の当たった時の関数
/// </summary>
/// <param name="collider"></param>
void BossEnemyRightArm::OnCollisionEnterActor(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			//SwingDown状態の時
			if (GetBossEnemy()->GetCurrentActionType() == BossEnemy::ActionType::SWINGDOWN)
			{
				
				DirectX::SimpleMath::Vector3 position = GetTransform()->GetWorldPosition();

				position.y = 0.1f;
				//パーティクルの通知
				Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::CREATE_PARTICLE_EFFECT, &position);
				m_hitSE->Play();
			}
		break;
		default:
			break;
	}

}



