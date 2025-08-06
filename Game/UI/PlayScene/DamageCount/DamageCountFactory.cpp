/*
	クラス名     : DamageCountFactory
	説明         : ダメージUIの作成クラスI
	補足・注意点 :
*/
#include "pch.h"
#include "DamageCountFactory.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/UI/PlayScene/DamageCount/DamageCount.h"
#include "Game/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Camera/Camera.h"
#include "Game/Messenger/Messengers.h"


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

	//通知を受け取るコンポーネントの追加
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::ENEMY_DAMAGE
		}
		, std::bind(&DamageCountFactory::Notify, this, std::placeholders::_1, std::placeholders::_2)
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

					ui->SetWorldPosition(data.Position);

					break;
				}
			}

			break;
		default:
			break;
	}

}
