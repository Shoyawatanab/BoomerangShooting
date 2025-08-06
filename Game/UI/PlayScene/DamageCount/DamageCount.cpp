/*
	クラス名     : DamageCount
	説明         : 敵のダメージUI
	補足・注意点 :
*/
#include "pch.h"
#include "DamageCount.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/Component/Components.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/NumberUI.h"
#include "Game/MathUtil.h"
#include "GameBase/Camera/Camera.h"



/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas"></param>
DamageCount::DamageCount(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_backGraund{}
	,m_numbers{}
	,m_usedNumbers{}
	,m_time{}
	,m_worldPosition{}
{
	using namespace DirectX::SimpleMath;



	////背景画像
	m_backGraund = GetScene()->AddActor<Image>(canvas,"DamageBackGraund");
	m_backGraund->GetTransform()->SetScale(BACKGROUND_SCALE);
	m_backGraund->GetTransform()->SetParent(GetTransform());

	//桁数
	for (int i = 0; i < MAXDIGITS; i++)
	{
		auto number = GetScene()->AddActor<NumberUI>(canvas);
		number->GetTransform()->SetScale(Vector3(2.3f, 2.3f,0));
		number->GetTransform()->SetParent(GetTransform());
		number->SetActive(false);
		m_numbers.push_back(number);
	}

	GetTransform()->SetScale(Vector3(0.1, 0.1, 0));
	//GetTransform()->SetPosition(Vector3(640, 360, 0));

	//初期化で非アクティブに
	SetActive(false);




}

/// <summary>
/// デストラクタ
/// </summary>
DamageCount::~DamageCount()
{
}

/// <summary>
/// 単体更新
/// </summary>
/// <param name="deltaTime">経過時間</param>
void DamageCount::UpdateActor(const float& deltaTime)
{
	//座標の更新
	UpdatePosition();

	if (m_time >= DISPLAYTIME)
	{
		SetActive(false);
		m_time = 0.0f;
		return;
	}

	m_time += deltaTime;
}

/// <summary>
/// オブジェクトがアクティブになった時に呼ばれる関数
/// </summary>
void DamageCount::OnEnable()
{

	//番号をすべて非アクティブに
	for (auto& number : m_numbers)
	{
		number->SetActive(false);
	}

}

/// <summary>
/// オブジェクトが非アクティブになった時に呼ばれる関数
/// </summary>
void DamageCount::OnDisable()
{

	//初期化
	m_usedNumbers.clear();



}

/// <summary>
/// 座標の更新
/// </summary>
void DamageCount::UpdatePosition()
{
	using namespace DirectX::SimpleMath;

	//座標をスクリーン座標に変換
	auto ScreenPos = MathUtil::WorldToScreen(m_worldPosition,
		Matrix::Identity,
		GetScene()->GetCamera()->GetViewMatrix(),
		GetScene()->GetCamera()->GetProjectionMatrix()
	);


	GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(ScreenPos.x, ScreenPos.y, 0));

}

/// <summary>
/// ダメージのセット
/// </summary>
/// <param name="damage"></param>
void DamageCount::SetDamage(int damage)
{
	using namespace DirectX::SimpleMath;

	//桁数を求める
	int digits = static_cast<int>(std::log10(damage) + 1);

	//最大桁数を超えていたら表示しない
	if (digits > MAXDIGITS)
	{
		return;
	}



	//桁数だけ回す
	for (int i = digits - 1; i >= 0; --i)
	{
		//表示番号のセット
		auto number = m_numbers[i];
		number->SetNumber(damage % 10);

		//表示座標の設定
		float offsetX = (i - (digits - 1) / 2.0f) * SPACING;

		Vector3 pos = Vector3(offsetX, 0, 0);

		number->GetTransform()->SetPosition(pos);
		number->SetActive(true);

		m_usedNumbers.push_back(number);

		damage /= 10;
	}


}

/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
void DamageCount::SetWorldPosition(DirectX::SimpleMath::Vector3 position)
{

	m_worldPosition = position;

	UpdatePosition();

}
