#include "pch.h"
#include "BoomerangThrowUI.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
BoomerangThrowUI::BoomerangThrowUI(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_leftThrow{}
	,m_rightThrow{}
{
	using namespace DirectX::SimpleMath;
	
	//右投げUI
	m_rightThrow = GetScene()->AddActor<Image>(canvas, "RightThrow");
	m_rightThrow->GetTransform()->SetPosition(RIGHT_UI_POSITION + OFFSET);
	m_rightThrow->GetTransform()->SetScale(RIGHT_UI_SCALE);
	//左投げUI
	m_leftThrow = GetScene()->AddActor<Image>(canvas, "LeftThrow");
	m_leftThrow->GetTransform()->SetPosition(LEFT_UI_POSITION);
	m_leftThrow->GetTransform()->SetScale(LEFT_UI_SCALE);


	//通知を受け取るコンポーネントの追加
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::MOUSE_WHEEL_UP
			,SceneMessageType::MOUSE_WHEEL_DOWN
		}
		, std::bind(&BoomerangThrowUI::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);


}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangThrowUI::~BoomerangThrowUI()
{
}


/// <summary>
/// 通知時に呼び出される関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BoomerangThrowUI::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);
	switch (type)
	{
		case SceneMessageType::MOUSE_WHEEL_UP:
			m_rightThrow->GetTransform()->SetPosition(RIGHT_UI_POSITION + OFFSET);
			m_leftThrow->GetTransform()->SetPosition(LEFT_UI_POSITION);
			break;
		case SceneMessageType::MOUSE_WHEEL_DOWN:
			m_rightThrow->GetTransform()->SetPosition(RIGHT_UI_POSITION );
			m_leftThrow->GetTransform()->SetPosition(LEFT_UI_POSITION + OFFSET);
			break;
		default:
			break;
	}

}
