#include "pch.h"
#include "BossEnemyBeam.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/Beam/Rays/BossEnemyBeamRays.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene"></param>
BossEnemyBeam::BossEnemyBeam(Scene* scene)
	:
	Actor(scene)
	,m_target{}
{

	//光線
	m_rays = GetScene()->AddActor<BossEnemyBeamRays>(GetScene());
	m_rays->GetTransform()->SetParent(GetTransform());

	//弾
	m_energyBall = GetScene()->AddActor<BossEnemyBeamEnergyBall>(GetScene());
	m_energyBall->GetTransform()->SetParent(GetTransform());

	GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(-1.6f, 4, 0));


	SetActive(false);
}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyBeam::~BossEnemyBeam()
{
}

/// <summary>
/// 個別のアップデート
/// </summary>
/// <param name="deltaTime"></param>
void BossEnemyBeam::UpdateActor(const float& deltaTime)
{



}

/// <summary>
/// ターゲットに向けて回転
/// </summary>
/// <param name="deltaTime"></param>
void BossEnemyBeam::TargetToRotation()
{
	//ターゲットがなければ
	if (!m_target)
	{
		return;
	}


	using namespace DirectX::SimpleMath;


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
	GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(0, -pitch, 0.0f));


}
