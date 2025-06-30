#include "pch.h"
#include "BossEnemyRightArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"

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

	//以下追加部位の作成


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
		{

			DirectX::SimpleMath::Vector3 position = GetTransform()->GetWorldPosition();

			position.y = 0.1f;

			SceneMessenger::GetInstance()->Notify(SceneMessageType::CREATE_PARTICLE_EFFECT, &position);
		}
		break;
		default:
			break;
	}

}



