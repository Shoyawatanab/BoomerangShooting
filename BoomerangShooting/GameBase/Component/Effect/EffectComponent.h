#pragma once
#include "GameBase/Component.h"
#include "GameBase/Component/Components.h"

class Camera;

class EffectComponent : public Component
{
public:
	//コンストラクタ
	EffectComponent(Actor* owner, std::function<void(const Camera& camera)> renderFunction);
	//デストラクタ
	~EffectComponent() override;

	//描画
	void Render(const Camera& camera);

private:
	
	//描画
	std::function<void(const Camera& camera)> m_renderFunction;

};