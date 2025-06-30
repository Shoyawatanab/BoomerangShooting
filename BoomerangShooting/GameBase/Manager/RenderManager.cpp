#include "pch.h"
#include "RenderManager.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/Common/Commons.h"


#include "GameBase/Camera/Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
RenderManager::RenderManager()
	:
	m_models{}
	,m_colliders{}
	,m_basicEffect{}
	,m_batch{}
	,m_effects{}
	,m_layout{}
	,m_roundShadow{}
{
	
	using namespace DirectX;
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// プリミティブバッチ、ベーシックエフェクトを準備する
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

	//// 入力レイアウトを作成する
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionColor>(
			device,
			m_basicEffect.get(),
			m_layout.ReleaseAndGetAddressOf()
		)
	);
	
}


/// <summary>
/// デストラクタ
/// </summary>
RenderManager::~RenderManager()
{
	m_models.clear();
	m_colliders.clear();
	m_uis.clear();
	m_effects.clear();
	m_roundShadow.clear();
}


/// <summary>
/// 描画
/// </summary>
/// <param name="view"></param>
/// <param name="projection"></param>
void RenderManager::Render(const Camera& camera)
{
	for (auto& model : m_models)
	{
		if (!model->GetActive()) { continue; }
		model->Render(camera);
	}

	for (auto& shadow : m_roundShadow)
	{
		if(!shadow->GetActive()) { continue; }
		shadow->Render(camera);
	}

	for (auto& effect : m_effects)
	{
		if (!effect->GetActive()) { continue; }
		effect->Render(camera);
	}

	for (auto& ui : m_uis)
	{
		if (!ui->GetActive()) { continue; }

		ui->Render();
	}
	


	//デバック実行時のみ処理
#ifdef _DEBUG
	for (auto& collider : m_colliders)
	{
		if (collider->GetActive())
		{
			collider->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(), m_batch.get(), m_basicEffect.get(), m_layout.Get());

		}
	}
#endif
}

/// <summary>
/// モデルの追加
/// </summary>
/// <param name="comp"></param>
void RenderManager::AddModel(ModelComponent* comp)
{
	//モデルがあるか
	auto model = std::find(m_models.begin(), m_models.end(), comp);

	//なければ
	if (model == m_models.end())
	{
		//追加
		m_models.push_back(std::move(comp));

	}


}

/// <summary>
/// モデルの削除
/// </summary>
/// <param name="comp"></param>
void RenderManager::RemoveModel(ModelComponent* comp)
{
	//モデルがあるか
	auto model = std::find(m_models.begin(), m_models.end(),comp);
	//あれば
	if (model != m_models.end())
	{
		//削除
		m_models.erase(model);

	}


}

/// <summary>
/// UIコンポーネントの追加
/// </summary>
/// <param name="comp">UIコンポーネント</param>
void RenderManager::AddUserInterface(ImageComponent* comp)
{
	//UIがあるか
	auto ui = std::find(m_uis.begin(), m_uis.end(), comp);

	//なければ
	if (ui == m_uis.end())
	{
		//追加
		m_uis.push_back(std::move(comp));

	}
}

/// <summary>
/// UIコンポーネントの削除
/// </summary>
/// <param name="comp">UIコンポーネント</param>
void RenderManager::RemoveUserInterface(ImageComponent* comp)
{
	//UIがあるか
	auto ui = std::find(m_uis.begin(), m_uis.end(), comp);
	//あれば
	if (ui != m_uis.end())
	{
		//削除
		m_uis.erase(ui);

	}
}

void RenderManager::AddCollider(ColliderComponent* comp)
{
//デバック実行時のみ処理
#ifdef _DEBUG

	//モデルがあるか
	auto collider = std::find(m_colliders.begin(), m_colliders.end(), comp);

	//なければ
	if (collider == m_colliders.end())
	{
		//追加
		m_colliders.push_back(comp);
	}
#endif


}

/// <summary>
/// エフェクトコンポーネントの追加
/// </summary>
/// <param name="comp">コンポーネント</param>
void RenderManager::AddEffect(EffectComponent* comp)
{
	//あるかさがす
	auto effect = std::find(m_effects.begin(), m_effects.end(), comp);

	//なければ
	if (effect == m_effects.end())
	{
		m_effects.push_back(comp);
	}


}

/// <summary>
/// 丸影の追加
/// </summary>
/// <param name="comp">コンポーネント</param>
void RenderManager::AddRoundShadow(RoundShadowComponent* comp)
{

	auto roundShadow = std::find(m_roundShadow.begin(), m_roundShadow.end(), comp);

	if (roundShadow == m_roundShadow.end())
	{
		m_roundShadow.push_back(comp);
	}



}


