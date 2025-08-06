/*
	クラス名     : BirdEnemy
	説明         : 鳥敵
	補足・注意点 :
*/
#include "pch.h"
#include "BirdEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BirdEnemy/Model/BirdEnemyModel.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Params.h"
#include "Game/Enemies/EnemyManager.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="player">プレイヤ</param>
BirdEnemy::BirdEnemy(Scene* scene, DirectX::SimpleMath::Vector3 scale
	, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation
	, EnemyManager* manager, Player* player)
	:
	EnemyBase(scene,Params::BIRDENEMY_HP,manager)
	,m_target{player}
	,m_bullets{}
{

	using namespace DirectX::SimpleMath;

	//当たり判定の追加
	AddComponent<AABB>(this, CollisionType::COLLISION
		, Vector3(1.5f,1.5f,1.5f) * scale
		, 3.0f * std::max({ scale.x, scale.y, scale.z }));

	//影の追加
	auto shadow = AddComponent<RoundShadowComponent>(this, Params::BIRDENEMY_SHADOW_RADIUS);

	shadow->SetActive(false);

	//モデルの作成
	auto model = GetScene()->AddActor<BirdEnemyModel>(GetScene());
	//親子関係をセット
	model->GetTransform()->SetParent(GetTransform());
	//モデルのセット
	SetModel(model);
	//自身をターゲットとして登録
	GetEnemyManger()->AddTargets({ this });

	//弾の作成
	for (int i = 0; i < MAX_BULLET; i++)
	{
		auto bullet = GetScene()->AddActor<BirdEnemyBullet>(GetScene(), this);
		
		m_bullets.push_back(bullet);
	}

	//初期状態の適用 Jsonで管理
	GetTransform()->SetScale(scale);
	GetTransform()->Translate(position);
	GetTransform()->SetRotate(rotation);

	//ステートマシーンの作成
	m_stateMachine = std::make_unique<BirdEnemyStateMachine>(this);


}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemy::~BirdEnemy()
{
}

/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime"></param>
void BirdEnemy::UpdateActor(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (FadeManager::GetInstance()->GetIsFade())
	{
		return;
	}

	//ステートマシーンの更新
	m_stateMachine->Update(deltaTime);

	//常にターゲットに向くように
	Rotate(deltaTime);

}

/// <summary>
/// 
/// </summary>
/// <param name="collider"></param>
void BirdEnemy::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::BOOMERANG:
		{
			//HPの減少
			HpDecrease(Params::BOOMERANG_DAMAGE);

		}

		//Hpが０になれば
		if (GetHp() <= 0)
		{
			//追加データの作成
			ExplosionEffectDatas datas;
			datas.Position = GetTransform()->GetWorldPosition();
			datas.Scale = GetTransform()->GetWorldScale();
			//爆発エフェクトの通知
			Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::EXPLOSITION_EFFECT, &datas);
			//オブジェクトを無効に
			SetActive(false);
			//マネージャーに死亡の通知
			auto manager = GetEnemyManger();
			manager->DeathEnemy(this);
		}
		else
		{
			//構造体の作成
			EnemyDamageDatas datas;
			//データのセット
			datas.Damage = Params::BOOMERANG_DAMAGE;
			datas.Position = GetTransform()->GetWorldPosition();
			//敵ダメージのUIの通知
			Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::ENEMY_DAMAGE, &datas);
		}

			break;
		default:
			break;
	}

}


/// <summary>
/// ターゲットに対して回転
/// </summary>
/// <param name="deltaTime"></param>
void BirdEnemy::Rotate(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(deltaTime);

	//敵の現在の座標の取得
	Vector3 enemyPosition = GetTransform()->GetWorldPosition();
	//プレイヤの現在の座標の取得
	Vector3 playerPosition = m_target->GetTransform()->GetWorldPosition();
	//敵からプレイヤの方向ベクトルの計算
	Vector3 toPlayer = playerPosition - enemyPosition;
	//yawの計算　（左右回転）
	//xz平面で敵からプレイヤの方向を求める
	float yaw = atan2(toPlayer.x, toPlayer.z);
	//pitchの計算（上下回転）
	//敵からプレイヤのウ違勅方向を求める
	float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));

	//yaw pitchから回転を計算 pitchは反転させる
	GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f));

}

/// <summary>
/// 非アクティブの弾の取得
/// </summary>
/// <returns>弾 or nullptr</returns>
BirdEnemyBullet* BirdEnemy::GetInactiveBullet()
{

	for (auto& bullet : m_bullets)
	{
		if (!bullet->GetActive())
		{
			return bullet;
		}
	}


	return nullptr;

}





