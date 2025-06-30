#include "pch.h"
#include "BossHp.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
BossHp::BossHp(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;

	//背景
	m_backGraund = GetScene()->AddActor<Image>(canvas, "BossHPBase");
	m_backGraund->GetTransform()->SetPosition(Vector3( 640, 50,0));
	m_backGraund->GetTransform()->SetScale(Vector3( 1, 0.9,0));

	//Hpバー
	m_hpBar = GetScene()->AddActor<Image>(canvas, "EnemyHP");
	m_hpBar->GetTransform()->SetPosition(Vector3(640, 50.5, 0));
	m_hpBar->GetTransform()->SetScale(Vector3(1, 0.85, 0));



	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOSS_DAMAGE
		}, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
BossHp::~BossHp()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BossHp::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::BOSS_DAMAGE:
		{
			//キャストして割合を求める
			float* ratio = static_cast<float*>(datas);
			//正しくキャストできているか

			if (typeid(*ratio) == typeid(float))
			{
				//Hpバーの塗りつぶし割合の変更
				m_hpBar->SetHorizontalFillAmount(*ratio);
			}
		}
			break;
		default:
			break;
	}
}
