#include "pch.h"
#include "NumberUI.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/UI/Image.h"

NumberUI::NumberUI(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_number{}
{
	using namespace DirectX::SimpleMath;

	m_number = GetScene()->AddActor<Image>(canvas, "Number");
	m_number->GetTransform()->SetScale(Vector3(0.01f, 0.01f, 0));
	//親子関係
	m_number->GetTransform()->SetParent(GetTransform());

	auto comp = m_number->GetComponent<ImageComponent>();
	//表示範囲の設定
	comp->SetViewRange(Vector2(0.1f,1.0f));

	//初期化
	SetNumber(0);

}

/// <summary>
/// デストラクタ
/// </summary>
NumberUI::~NumberUI()
{
}

/// <summary>
/// 数字の登録
/// </summary>
/// <param name="number"></param>
void NumberUI::SetNumber(int number)
{
	using namespace DirectX::SimpleMath;

	//数字の応じた切り取り
	m_number->SetCutRange(Vector4(0.1f * number, 0, DIGITWIDTH, 1.0f));


}
