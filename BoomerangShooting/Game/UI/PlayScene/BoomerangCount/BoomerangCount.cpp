#include "pch.h"
#include "BoomerangCount.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
BoomerangCount::BoomerangCount(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;


	//真ん中のUIがゼロ座標になるようにしている

	auto image1 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image1->GetTransform()->SetParent(GetTransform());

	image1->GetTransform()->SetScale(BOOMERANG_SCALE);
	image1->GetTransform()->SetPosition(-OFFSET_POSITION);
	
	m_boomerangUI.push_back(image1);

	auto image2 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image2->GetTransform()->SetParent(GetTransform());

	image2->GetTransform()->SetScale(BOOMERANG_SCALE);
	image2->GetTransform()->SetPosition(Vector3::Zero);

	m_boomerangUI.push_back(image2);

	auto image3 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image3->GetTransform()->SetParent(GetTransform());

	image3->GetTransform()->SetScale(BOOMERANG_SCALE);
	image3->GetTransform()->SetPosition(OFFSET_POSITION);

	m_boomerangUI.push_back(image3);


	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITION);

	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOOMERANG_THROW
			,SceneMessageType::BOOMERANG_CATCH
		}, this
	);



}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangCount::~BoomerangCount()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BoomerangCount::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{
		case SceneMessageType::BOOMERANG_THROW:
			//配列の後ろから探す
			for (int i = static_cast<int>( m_boomerangUI.size() - 1); i >= 0; --i)
			{
				//アクティブ状態のものがあれば
				if (m_boomerangUI[i]->GetActive())
				{
					//非アクティブに
					m_boomerangUI[i]->SetActive(false);
					break;
				}
			}
			break;
		case SceneMessageType::BOOMERANG_CATCH:
			//配列順に回す
			for (int i = 0 ; i < m_boomerangUI.size(); i++)
			{
				//非アクティブ状態のものがあれば
				if (!m_boomerangUI[i]->GetActive())
				{
					//アクティブに
					m_boomerangUI[i]->SetActive(true);
					break;
				}
			}
			break;
		default:
			break;
	}

}
