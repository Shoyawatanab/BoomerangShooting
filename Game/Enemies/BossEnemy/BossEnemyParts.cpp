/*
	クラス名     : BossEnemy
	説明         : ボス敵のパーツの基底クラス
	補足・注意点 :
*/
#include "pch.h"
#include "BossEnemyParts.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Params.h"
#include "Game/Messenger/Messengers.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="partsName">パーツ名</param>
/// <param name="modelName">モデル名</param>
/// <param name="hp">パーツHP</param>
/// <param name="boss">大本のクラス</param>
BossEnemyParts::BossEnemyParts(Scene* scene, std::string partsName,std::string modelName
	,int hp, DirectX::SimpleMath::Vector3 boxColliderExtens, float sphereRadius
	, BossEnemy* boss)
	:
	ModelPartsBase(scene,partsName,modelName)
	,m_hp{hp}
	,m_bossEnemy{boss}
{
	//共感リソースの取得
	m_commonResources = CommonResources::GetInstance();
	//当たり判定の追加
	auto obb = AddComponent<OBB>(this,  CollisionType::TRIGGER
		, boxColliderExtens
		, DirectX::SimpleMath::Quaternion::Identity
		, sphereRadius);
	//当たり判定を行わないタグの追加
	obb->SetNotHitObjectTag({
		Actor::ObjectTag::BOSS_ENEMY
		});
	//重力の追加
	auto rigigdBody = AddComponent<RigidbodyComponent>(this);
	rigigdBody->SetActive(false);


	//カスタム描画の追加
	GetModelComponent()->SetCustomRenderFunction(std::bind(&BossEnemyParts::Render, this, std::placeholders::_1));
}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyParts::~BossEnemyParts()
{
}

/// <summary>
/// 当たった時の関数
/// </summary>
/// <param name="collider">相手のコライダー</param>
void BossEnemyParts::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case ObjectTag::BOOMERANG:
		{
			//パーツのHp減少
			HpDecrease(Params::BOOMERANG_DAMAGE);

			//構造体の作成
			EnemyDamageDatas datas;
			//データのセット
			datas.Damage = Params::BOOMERANG_DAMAGE;
			datas.Position = GetTransform()->GetWorldPosition();

			Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::ENEMY_DAMAGE, &datas);

			//ボス敵にダメージの加算
			m_bossEnemy->AddDamage(Params::BOOMERANG_DAMAGE);


		}
			break;
		default:
			break;
	}

	//パーツごとの判定
	OnCollisionEnterActor(collider);

}

/// <summary>
/// HP減少
/// </summary>
/// <param name="damage">ダメージ</param>
void BossEnemyParts::HpDecrease(int damage)
{
	//すでに破壊されているなら処理しないため
	if (m_hp == 0)
	{
		return;
	}
	//HPの減少
	m_hp -= damage;
	//0以下にならないように
	m_hp = std::max(m_hp, 0);

	if (m_hp == 0)
	{
		//パーツごとの破壊処理
		PartsDestruction();
		//ボス敵に部位破壊ダメージの加算
		m_bossEnemy->AddDamage(Params::BOOMERANG_DAMAGE * 5);

		//爆発エフェクトの通知
		ExplosionEffectDatas datas;
		//追加データからデータのセット
		datas.Position = GetTransform()->GetWorldPosition();
		datas.Scale = GetTransform()->GetWorldScale();
		Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::EXPLOSITION_EFFECT, &datas);


	}

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="camera">カメラ</param>
void BossEnemyParts::Render(const Camera& camera)
{
	auto model = GetModelComponent()->GetModel();

	if (m_hp <= 0)
	{
		// モデルのエフェクトを更新する
		model->UpdateEffects([&](DirectX::IEffect* effect)
			{
				// ベイシックエフェクトを取得する
				auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
				// ディフューズカラーを設定する
				basicEffect->SetDiffuseColor(DirectX::Colors::Black);
				// スペキュラカラーを設定する
				basicEffect->SetSpecularColor(DirectX::Colors::Black);
				// スペキュラパワーを設定する
				basicEffect->SetSpecularPower(20.0f);
			});

	}
	else
	{
		// モデルのエフェクトを更新する
		model->UpdateEffects([&](DirectX::IEffect* effect)
			{
				// ベイシックエフェクトを取得する
				auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
				// ディフューズカラーを設定する
				basicEffect->SetDiffuseColor(DirectX::Colors::LightSlateGray);
				// スペキュラカラーを設定する
				basicEffect->SetSpecularColor(DirectX::Colors::LightSlateGray);
				// スペキュラパワーを設定する
				basicEffect->SetSpecularPower(20.0f);
			});

	}

	//モデル描画
	model->Draw(m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
		, *m_commonResources->GetCommonStates()
		, GetTransform()->GetWorldMatrix()
		, camera.GetViewMatrix()
		, camera.GetProjectionMatrix());
}
