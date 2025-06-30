#include "pch.h"
#include "TargetMarker.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Screen.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/Actor.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/MathUtil.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">キャンバス</param>
/// <param name="targets">ターゲット配列</param>
TargetMarker::TargetMarker(Canvas* canvas, std::vector<Actor*> targets)
	:
	Actor(canvas->GetScene())
	,m_marker{}
	,m_targets{targets}
	,m_isGetReady{false}
	,m_isLockOn{false}
{

	using namespace DirectX::SimpleMath;

	m_marker = GetScene()->AddActor<Image>(canvas,"TargetMarker");
	///m_marker->SetActive(false);
	m_marker->GetTransform()->SetScale(SCALE);

	m_marker->GetTransform()->SetPosition(Vector3::Zero);
	m_marker->SetActive(false);

	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_GET_REDAY
			,SceneMessageType::PLAYER_GET_REDAY_END
		}
		, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
TargetMarker::~TargetMarker()
{
}

/// <summary>
/// 単体の更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void TargetMarker::UpdateActor(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	if (!m_isGetReady) { return; }

	Vector2 result = FilterWithinRange();

	m_marker->GetTransform()->SetPosition(Vector3(result.x, result.y, 0.0f));



}


void TargetMarker::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::NONE:
			break;
		case SceneMessageType::PLAYER_GET_REDAY:
			m_isGetReady = true;
			break;
		case SceneMessageType::PLAYER_GET_REDAY_END:
			m_isGetReady = false;
			m_marker->SetActive(false);
			break;
		default:
			break;
	}
}

/// <summary>
/// 範囲内かどうかさがす
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector2 TargetMarker::FilterWithinRange()
{

	using namespace DirectX::SimpleMath;
	//変数宣言
	DirectX::SimpleMath::Vector2 result;

	m_marker->SetActive(false);
	m_isLockOn = false;

	//画面の横のサイズを初期値とする
	float minLength = Screen::WIDTH;


	//
	for (const auto& point : m_targets)
	{
		//座標をスクリーン座標に変換
		Vector2 ScreenPos = MathUtil::WorldToScreen(point->GetTransform()->GetWorldPosition(),
			Matrix::Identity,
			GetScene()->GetCamera()->GetViewMatrix(),
			GetScene()->GetCamera()->GetProjectionMatrix()
		);

		float distance = Vector2::Distance(ScreenPos, Vector2(Screen::CENTER_X,Screen::CENTER_Y));

		//raneg内の座標かどうかの判定
		if (distance <= RANGE)
		{
			//最小値よりも小さければ
			if (minLength > distance)
			{

				//配列に格納
				result = ScreenPos;
				//最小値を更新
				minLength = distance;
				//ターゲットを更新
				m_targetPosition = point->GetTransform()->GetWorldPosition();

				m_marker->SetActive(true);
				m_isLockOn = true;
			}

		}
	}

	return result;
}

