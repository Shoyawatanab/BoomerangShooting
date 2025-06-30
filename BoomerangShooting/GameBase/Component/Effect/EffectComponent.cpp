#include "pch.h"
#include "EffectComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "GameBase/Component/Components.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="renderFunction">描画関数</param>
EffectComponent::EffectComponent(Actor* owner, std::function<void(const Camera& camera)> renderFunction)
	:
	Component(owner)
	,m_renderFunction{renderFunction}
{

	using namespace DirectX;


	//マネージャーに追加
	GetActor()->GetScene()->GetRenderMangaer()->AddEffect(this);

}

/// <summary>
/// デストラクタ
/// </summary>
EffectComponent::~EffectComponent()
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void EffectComponent::Render(const Camera& camera)
{
	//個別描画
	m_renderFunction(camera);
}


