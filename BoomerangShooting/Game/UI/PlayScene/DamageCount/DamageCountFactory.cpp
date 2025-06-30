#include "pch.h"
#include "DamageCountFactory.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/UI/PlayScene/DamageCount/DamageCount.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "GameBase/Component/Components.h"
#include "Game/MathUtil.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Camera/Camera.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
DamageCountFactory::DamageCountFactory(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_damageCount{}
{
	//定数文事前に作成
	for (int i = 0; i < MAX; i++)
	{
		auto damageCount = GetScene()->AddActor<DamageCount>(canvas);
		m_damageCount.push_back(damageCount);
	}

	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::ENEMY_DAMAGE
		}, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
DamageCountFactory::~DamageCountFactory()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void DamageCountFactory::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{
		case SceneMessageType::ENEMY_DAMAGE:
			
			for (auto& ui : m_damageCount)
			{
				//非アクティブなら
				if (!ui->GetActive())
				{
					//アクティブに
					ui->SetActive(true);

					EnemyDamageDatas data = *static_cast<EnemyDamageDatas*>(datas);

					//追加データからダメージをキャスト
					ui->SetDamage(data.Damage);

					//座標をスクリーン座標に変換
					auto ScreenPos = MathUtil::WorldToScreen(data.Position,
						DirectX::SimpleMath::Matrix::Identity,
						GetScene()->GetCamera()->GetViewMatrix(),
						GetScene()->GetCamera()->GetProjectionMatrix()
					);


					ui->GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(ScreenPos.x,ScreenPos.y,0));

					break;
				}
			}

			break;
		default:
			break;
	}

}
