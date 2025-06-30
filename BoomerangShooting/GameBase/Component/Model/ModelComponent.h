#pragma once
#include "GameBase/Component/Components.h"

class CommonResources;
class Camera;

class ModelComponent : public Component
{
public:

	//描画種類
	enum class RenderKinds
	{
		NORMAL    //通常
		, CUSTOM	  //カスタム
	};
public:

	//カスタム描画関数の登録
	void SetCustomRenderFunction(std::function<void(const Camera& camera)> customRender);
	//モデルの取得
	DirectX::Model* GetModel() { return m_model; }

public:
	//コンストラクタ
	ModelComponent(Actor* owner, std::string modelMame);
	//デストラクタ
	~ModelComponent() override;
	//描画
	void Render(const Camera& camera);

private
	:
	//通常描画
	void NormalRender(const Camera& camera);
	//カスタム描画
	void CustomRender(const Camera& camera);

private:
	//モデル
	DirectX::Model* m_model;
	//共通リソース
	CommonResources* m_commonResources;

	//個別描画
	std::function<void(const Camera& camera)> m_customRender;
	//描画の種類
	RenderKinds m_renderKinds;


};