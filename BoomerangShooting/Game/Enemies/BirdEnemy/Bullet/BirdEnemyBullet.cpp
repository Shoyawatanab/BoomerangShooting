#include "pch.h"
#include "BirdEnemyBullet.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStateMachine.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
BirdEnemyBullet::BirdEnemyBullet(Scene* scene, BirdEnemy* birdEnemy)
	:
	Actor(scene)
	,m_birdEnemy{birdEnemy}
	,m_explosionSE{}
{

	using namespace DirectX::SimpleMath;

	//コンポーネントの追加
	AddComponent<ModelComponent>(this, "BeamEnergyBall");

	//当たり判定の作成
	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, BOX_COLLIDER_SIZE
		, SPHERE_COLLIDER_SIZE);

	//丸影
	auto shadow = AddComponent<RoundShadowComponent>(this, 0.6f);
	//爆発音の作成
	m_explosionSE = AddComponent<SoundComponent>(this, "Explosion", SoundComponent::SoundType::SE);

	//初期状態
	GetTransform()->SetScale(Vector3(0.5f,0.5f,0.5f));
	GetTransform()->SetPosition(Vector3(0,0,3));

	//親子関係を結ぶ
	GetTransform()->SetParent(birdEnemy->GetTransform());

	//ステートマシーンの作成
	m_stateMachine = std::make_unique<BirdEnemyBulletStateMachine>(this,birdEnemy);

}


/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBullet::~BirdEnemyBullet()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BirdEnemyBullet::UpdateActor(const float& deltaTime)
{
	m_stateMachine->Update(deltaTime);
}


/// <summary>
/// 当たった時の関数
/// </summary>
/// <param name="collider"></param>
void BirdEnemyBullet::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::PLAYER:
		case Actor::ObjectTag::STAGE:
		{
			//爆発エフェクトの通知
			ExplosionEffectDatas datas;
			//追加データからデータのセット
			datas.Position = GetTransform()->GetWorldPosition();
			datas.Scale = GetTransform()->GetWorldScale();
			SceneMessenger::GetInstance()->Notify(SceneMessageType::EXPLOSITION_EFFECT,&datas);
			
			//SEの再生
			m_explosionSE->Play();
			//状態の変化
			m_stateMachine->ChangeState(BirdEnemyBulletState::IDEL);

		}
			break;
		default:
			break;
	}


}


