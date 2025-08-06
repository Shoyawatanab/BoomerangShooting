/*
	クラス名     : BoomerangFadeOut
	説明         : ブーメラン型のフェードアウト
	補足・注意点 :
*/
#pragma once
#include "Game/Fade/IFade.h"

class BoomerangFadeOut : public IFade
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

	// フェードの時間
	static constexpr float FADE_TIME = 1.0f;
	// フェードの初期サイズ
	static constexpr float FADE_FIRST_SIZE = 1.25f;
	// フェードの最大サイズ
	static constexpr float FADE_MAX_SIZE = 24.0f;
	// フェードのしきい値
	static constexpr float FADE_THRESHOLD = 0.7f;

public:

	//コンストラク
	BoomerangFadeOut();
	//デストラクタ
	~BoomerangFadeOut() override;
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
	void CreateShader();
	// フェード量を計算する
	float CalcrateFadeValue(float easing);
	// 型抜き画像の描画処理
	void DrawStencilImage();

private:
	//コンストバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//マスク用入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_maskInputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	//	使用する頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	使用するピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	使用するジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//マスク用頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_maskVS;
	//マスク用ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_maskPS;
	//マスク用ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_maskGS;

	// ロード画面として使用するテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// マスク用のテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stencilImage;
	// 型抜き画像のみの描画結果を持つ画像
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_capture;
	// 型抜き画像のみの描画結果を持つ画像のビュー
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_captureRTV;
	// 型抜き画像のみの描画結果を持つ画像のシェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_captureSRV;
	// 経過時間
	float m_totalTime;
};
