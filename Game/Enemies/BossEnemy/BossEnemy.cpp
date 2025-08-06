/*
	クラス名     : BossEnemy
	説明         : ボス敵
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
#include "Game/Enemies/BossEnemy/BehavirTree/BossBehaviorTree.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Model/BossEnemyModel.h"
#include "Game/Enemies/BossEnemy/Animation/BossAnimationController.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActionManager.h"
#include "Game/Player/Player.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"
#include "Game/Enemies/EnemyManager.h"
#include "Game/Messenger/Messengers.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="player">プレイヤ</param>
BossEnemy::BossEnemy(Scene* scene, DirectX::SimpleMath::Vector3 scale
	, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation
	, EnemyManager* manager, Player* player)
	:
	EnemyBase(scene,Params::BOSSENEMY_MAX_HP,manager)
	,m_behavior{}
	,m_actionManager{}
	,m_animation{}
	,m_isGround{}
	,m_player{player}
{

	using namespace DirectX::SimpleMath;


	m_rigidBody = AddComponent<RigidbodyComponent>(this);
	//当たり判定の作成
	auto collider = AddComponent<AABB>(this,  CollisionType::COLLISION
		, Params::BOSSENEMY_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_SPHERE_COLLIDER_SIZE);

	collider->SetNotHitObjectTag({
		Actor::ObjectTag::BOSS_ENEMY_PARTS
		,Actor::ObjectTag::BEAM

		});


	AddComponent<RoundShadowComponent>(this, Params::BOSSENEMY_SHADOW_RADIUS);


	//モデルの作成
	auto model = GetScene()->AddActor<BossEnemyModel>(GetScene(),this);
	//親子関係をセット
	model->GetTransform()->SetParent(GetTransform());
	
	SetModel(model);

	//着地音
	m_landingSE = AddComponent<SoundComponent>(this, "Landing", SoundComponent::SoundType::SE);



//パーツをマネージャーにターゲットとして登録
	//パーツの取得
	auto partss = model->GetParts();
	//保存配列
	std::vector<Actor*> partssActor;
	for (auto& part : partss)
	{
		//Actorだけを抽出する
		partssActor.push_back(part.second);
	}
//ここまで

	GetEnemyManger()->AddTargets(partssActor);

	//初期状態の適用
	GetTransform()->SetScale(scale);
	GetTransform()->Translate(position);
	GetTransform()->SetRotate(rotation);

	auto beam = GetScene()->AddActor<BossEnemyBeam>(GetScene());
	beam->GetTransform()->SetParent(GetTransform());
	beam->SetTarget(player);

	//ビヘイビアツリー
	m_behavior = std::make_unique<BossBehaviorTree>(player,this);

	//アニメーションコンポーネントの追加
	m_animation = AddComponent<AnimatorComponent>(this, std::make_unique<BossAnimationController>(this));
	//アクションマネージャーの作成
	m_actionManager = std::make_unique<BossEnemyActionManager>(this,player,beam);



}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemy::~BossEnemy()
{

}



/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime"></param>
void BossEnemy::UpdateActor(const float& deltaTime)
{
	//フェード実行中
	if (FadeManager::GetInstance()->GetIsFade())
	{

		return;
	}


	//アクションの更新
	if (m_actionManager->Update(deltaTime))
	{
		//ビヘイビアツリーの更新
		m_behavior->Update(deltaTime);
	}

}

/// <summary>
/// 当たった時に呼ばれる関数
/// </summary>
/// <param name="collider">相手のコライダー</param>
void BossEnemy::OnCollisionEnter(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			Landing();
			break;
		case Actor::ObjectTag::BOOMERANG:

			break;
		default:
			break;
	}

}



/// <summary>
/// 当たっているときに呼び出される関数
/// </summary>
/// <param name="collider">相手のコライダー</param>
void BossEnemy::OnCollisionStay(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			Landing();
			break;
		default:
			break;
	}
}

/// <summary>
/// 離れた時に呼び出される関数
/// </summary>
/// <param name="collider"></param>
void BossEnemy::OnCollisionExit(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			m_isGround = false;
			break;
		default:
			break;
	}
}

/// <summary>
/// ダメージを食らったとき
/// </summary>
/// <param name="damage">ダメージ</param>
void BossEnemy::AddDamage(int damage)
{

	HpDecrease(damage);
	


	float ratio = GetHpRatio();
	Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::BOSS_DAMAGE, &ratio);


	if (GetHp() <= 0)
	{
		auto camera = GetScene()->GetCamera();

		auto* playCamera = static_cast<PlaySceneCamera*>(camera);
		playCamera->SetTarget(this);

		//アクションの停止
		m_actionManager->ActionCancel();

		m_actionManager->ChangeAction("Death");

	}
	

}

/// <summary>
/// 回転
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BossEnemy::Rotation(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	auto ownerPosition = GetTransform()->GetPosition();

	auto targetPosition = m_player->GetTransform()->GetPosition();

	ownerPosition.y = 0.0f;
	targetPosition.y = 0.0f;

	//向きたい方向
	Vector3 direction = targetPosition - ownerPosition;
	direction.Normalize();
	//今の敵の前方向
	Vector3 forward = GetTransform()->GetForwardVector();
	//forward.Normalize();
	//回転軸の作成
	Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//正なら上方向
		moveAxis = Vector3::Up;
	}
	else
	{
		//負なら下方向
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(direction);

	moveAngle = std::clamp(moveAngle, -1.0f, 1.0f);

	//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * deltaTime);

	//敵の回転の取得
	DirectX::SimpleMath::Quaternion Rotate = GetTransform()->GetRotate();
	//Y軸に対して回転をかける
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	GetTransform()->SetRotate(Rotate);

}

/// <summary>
/// 着地音の再生
/// </summary>
void BossEnemy::PlayLandingSE()
{
	//着地音
	m_landingSE->Play();

}

/// <summary>
/// 着地したとき
/// </summary>
void BossEnemy::Landing()
{
	m_rigidBody->ResetGravity();
	m_isGround = true;
}
















