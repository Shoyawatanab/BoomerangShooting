#include "pch.h"
#include "ResuktTime.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/UI/NumberUI.h"
#include "Game/UI/ResultScene/Time/TimeSeparator.h"
#include "Game/GlobalGameData.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
ResuktTime::ResuktTime(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_time{}
{
	using namespace DirectX::SimpleMath;

	//桁数の作成
	//分の10の位
	auto number = GetScene()->AddActor<NumberUI>(canvas);
	number->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0));
	number->GetTransform()->SetPosition(Vector3(-LETTER_SPACING * 2,0, 0));
	number->GetTransform()->SetParent(GetTransform());
	m_numbers.push_back(number);
	
	//分の1の位
	number = GetScene()->AddActor<NumberUI>(canvas);
	number->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0));
	number->GetTransform()->SetPosition(Vector3(-LETTER_SPACING,0, 0));
	number->SetNumber(1);
	number->GetTransform()->SetParent(GetTransform());
	m_numbers.push_back(number);
	
	// 秒の10の位
	number = GetScene()->AddActor<NumberUI>(canvas);
	number->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0));
	number->GetTransform()->SetPosition(Vector3(LETTER_SPACING, 0, 0));
	number->SetNumber(1);
	number->GetTransform()->SetParent(GetTransform());
	m_numbers.push_back(number);

	// 秒の1の位
	number = GetScene()->AddActor<NumberUI>(canvas);
	number->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0));
	number->GetTransform()->SetPosition(Vector3(LETTER_SPACING * 2, 0, 0));
	number->SetNumber(1);
	number->GetTransform()->SetParent(GetTransform());
	m_numbers.push_back(number);


	//区切り点の作成
	m_separator = GetScene()->AddActor<TimeSeparator>(canvas);
	m_separator->GetTransform()->SetParent(GetTransform());


	GetTransform()->SetPosition(POSITION);

	AddTime(GlobalGameData::GetInstance()->GetClearTime());

}

/// <summary>
/// デストラクタ
/// </summary>
ResuktTime::~ResuktTime()
{
}

/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime">経過時間</param>
void ResuktTime::UpdateActor(const float& deltaTime)
{
	//点滅
	Blink(deltaTime);

}


/// <summary>
/// 時間の追加
/// </summary>
/// <param name="totalSecond"></param>
void ResuktTime::AddTime(const float& totalSeconds)
{

	//分を求める
	int minutes = totalSeconds / 60;
	//秒を求める
	int seconds = static_cast<int>(totalSeconds) % 60;

	//各桁に分解する
	int minuteTens = minutes / 10;    // 分の10の位
	int minuteOnes = minutes % 10;    // 分の1の位

	int secondTens = seconds / 10;    // 秒の10の位
	int secondOnes = seconds % 10;    // 秒の1の位

	//分のセット
	m_numbers[0]->SetNumber(minuteTens);
	m_numbers[1]->SetNumber(minuteOnes);

	//秒のセット
	m_numbers[2]->SetNumber(secondTens);
	m_numbers[3]->SetNumber(secondOnes);



}

/// <summary>
/// 点滅
/// </summary>
/// <param name="deltaTime"></param>
void ResuktTime::Blink(const float& deltaTime)
{
	
	if (m_time >= BLINK_INTERVAL)
	{
		//現在の状態の取得
		bool isActive = m_separator->GetActive();

		switch (isActive)
		{
			case true:
				//非アクティブ状態に
				m_separator->SetActive(false);
				break;
			case false:
				//アクティブ状態に
				m_separator->SetActive(true);
				break;
			default:
				break;
		}

		m_time = 0.0f;
	}


	m_time += deltaTime;
}
