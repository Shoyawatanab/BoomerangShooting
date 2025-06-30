#include "pch.h"
#include "ModelComponent.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Manager/RenderManager.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/GameResources.h"
#include "GameBase/Camera/Camera.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="modelMame">モデル名</param>
ModelComponent::ModelComponent(Actor* owner, std::string modelMame)
	:
	Component(owner)
	,m_commonResources{}
	,m_customRender{}
	,m_renderKinds{RenderKinds::NORMAL}
{

	m_commonResources = CommonResources::GetInstance();

	//モデルの取得
	m_model = GameResources::GetInstance()->GetModel(modelMame);

	GetActor()->GetScene()->GetRenderMangaer()->AddModel(this);

}

/// <summary>
/// デストラクタ
/// </summary>
ModelComponent::~ModelComponent()
{
	//削除
	GetActor()->GetScene()->GetRenderMangaer()->RemoveModel(this);

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="camera">カメラ</param>
void ModelComponent::Render(const Camera& camera)
{

	switch (m_renderKinds)
	{
		case ModelComponent::RenderKinds::NORMAL:
			NormalRender(camera);
			break;
		case ModelComponent::RenderKinds::CUSTOM:
			CustomRender(camera);
			break;
		default:
			break;
	}

}

/// <summary>
/// 通常描画
/// </summary>
/// <param name="camera">カメラ</param>
void ModelComponent::NormalRender(const Camera& camera)
{
	//モデル描画
	m_model->Draw(m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
		, *m_commonResources->GetCommonStates()
		, GetActor()->GetTransform()->GetWorldMatrix()
		, camera.GetViewMatrix()
		, camera.GetProjectionMatrix());
}

/// <summary>
/// カスタム描画
/// </summary>
/// <param name="camera">カメラ</param>
void ModelComponent::CustomRender(const Camera& camera)
{

	m_customRender(camera);

}


/// <summary>
/// カスタム描画関数の登録
/// </summary>
/// <param name="customRender">関数</param>
void ModelComponent::SetCustomRenderFunction(std::function<void(const Camera& camera)> customRender)
{
	m_customRender = customRender;
	//状態の変更
	m_renderKinds = RenderKinds::CUSTOM;

}



