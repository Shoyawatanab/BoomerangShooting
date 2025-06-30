#include "pch.h"
#include "UIManager.h"
#include "GameBase/Component/UI/ButtonComponent.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Actor.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Screen.h"

/// <summary>
/// コンストラク
/// </summary>
UIManager::UIManager()
	:
	m_buttom{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
UIManager::~UIManager()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">更新処理</param>
void UIManager::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//なければ
	if(m_buttom.empty()) 
	{
		return;
	}

	const auto& state = CommonResources::GetInstance()->GetInputManager()->GetMouseState();


	RECT rect{ CommonResources::GetInstance()->GetDeviceResources()->GetOutputSize() };

	//画面サイズの取得
	float widht = static_cast<float>(CommonResources::GetInstance()->GetDeviceResources()->GetOutputSize().right);
	float height = static_cast<float>(CommonResources::GetInstance()->GetDeviceResources()->GetOutputSize().bottom);

	Vector2 mousePosition = Vector2(state.x * Screen::WIDTH / widht, state.y * Screen::HEIGHT / height);

	for (auto& buttom : m_buttom)
	{
		//マウスとボタン範囲の判定
		if (CheckInRange(mousePosition, buttom))
		{
			buttom->InRange();

			const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();
			
			if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
			{

				buttom->OnClick();

			}
			break;
		}
		else
		{
			buttom->OutOfRange();
		}
	}

}

/// <summary>
/// ボタンの追加
/// </summary>
/// <param name="buttom"></param>
void UIManager::AddButtomComponent(ButtonComponent* buttom)
{

	m_buttom.push_back(buttom);

}

/// <summary>
/// ボタン範囲内かのチェック
/// </summary>
/// <param name="mousePosition">マウス座標</param>
/// <param name="buttom">ボタンコンポーネント</param>
/// <returns>true：当たった　false：当たってない</returns>
bool UIManager::CheckInRange(const DirectX::SimpleMath::Vector2& mousePosition, ButtonComponent* buttom)
{
	using namespace DirectX::SimpleMath;

	auto comp = buttom->GetActor()->GetComponent<ImageComponent>();

	Vector2 position = Vector2(buttom->GetActor()->GetTransform()->GetPosition().x,buttom->GetActor()->GetTransform()->GetPosition().y);
	Vector2 scale = Vector2(comp->GetWidth(),comp->GetHeight());

	// 四角形の境界座標を計算
	float rectLeft = position.x - scale.x / 2;
	float rectRight = position.x + scale.x / 2;
	float rectTop = position.y - scale.y / 2;
	float rectBottom = position.y + scale.x / 2;

	// 円の中心に最も近い四角形の点を求める
	float closestX = std::max(rectLeft, std::min(mousePosition.x, rectRight));
	float closestY = std::max(rectTop, std::min(mousePosition.y, rectBottom));

	// 円の中心と最近接点の距離を計算
	Vector2 diff = mousePosition - Vector2(closestX, closestY);
	float distanceSquared = diff.LengthSquared();

	// 当たり判定（距離の二乗が半径の二乗以下なら衝突）
	return distanceSquared <= (5 * 5);
}
