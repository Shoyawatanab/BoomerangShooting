#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"

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
