#pragma once
#include "Game/Fade/IFade.h"

class NormalFadeOut : public IFade
{
public:

	//コンスタントバッファ)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	time;
	};

	//インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//フェード時間
	static constexpr float MAX_TIME = 2.0f;

public:



public:

	//コンストラク
	NormalFadeOut();
	//デストラクタ
	~NormalFadeOut() override;
	//更新処理
	bool Update(const float& deltaTime) override;
	//描画
	void Render() override;

	//入った時
	void Enter() override;
	//抜けた時
	void Exit() override;

private:
	//シェーダー作成
	void CreateShader(ID3D11Device1* device, ID3D11DeviceContext* context);

private:
	//コンストバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	使用する頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	使用するピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	使用するジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	//時間
	float m_time;

};
