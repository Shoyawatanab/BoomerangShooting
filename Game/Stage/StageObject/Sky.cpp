/*
	クラス名     : Sky
	説明         : 天球
	補足・注意点 :
*/
#include "pch.h"
#include "Sky.h"
#include "Game/Component/Components.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
Sky::Sky(Scene* scene)
	:
	Actor(scene)
{

	//モデルコンポーネントの追加
	m_modelComponent =  AddComponent<ModelComponent>(this, "Sky");

	m_modelComponent->SetCustomRenderFunction(std::bind(&Sky::Render, this,std::placeholders::_1));



}

/// <summary>
/// デストラクタ
/// </summary>
Sky::~Sky()
{
	// do nothing.
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void Sky::Render(const Camera& camera)
{

	using namespace DirectX::SimpleMath;
	using namespace DirectX;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();

	auto model = m_modelComponent->GetModel();

	// モデルのエフェクト情報を更新する
	model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ベーシックエフェクトを設定する
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// 個別のライトをすべて無効化する
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// 環境光も無効化する
				basicEffect->SetAmbientLightColor(Colors::Black);

				// モデルを自発光させる
				basicEffect->SetEmissiveColor(Colors::White);
			}
		}
	);

	// ワールド行列を更新する
	Matrix world = Matrix::Identity;

	// モデルを描画する
	model->Draw(context, *states, world, camera.GetViewMatrix(), camera.GetProjectionMatrix());

}













