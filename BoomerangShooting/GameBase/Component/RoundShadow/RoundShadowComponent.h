#pragma once
#include "GameBase/Component.h"
#include "GameBase/Component/Components.h"


class RoundShadowComponent : public Component
{
public:
	//コンストラクタ
	RoundShadowComponent(Actor* owner,float radius);
	//デストラクタ
	~RoundShadowComponent() override;

	//描画
	void Render(const Camera& camera);

private:

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;

	// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// 深度ステンシルステート
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	//半径
	float m_radius;


};