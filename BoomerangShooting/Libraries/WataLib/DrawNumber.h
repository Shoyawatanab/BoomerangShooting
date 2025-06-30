//--------------------------------------------------------------------------------------
// File: DrawNumber.h
//
// ユーザーインターフェースクラス
//
//-------------------------------------------------------------------------------------

#pragma once

#include "GameBase/Common/Commons.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>



class DrawNumber
{
public:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:
	//データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

public:

	void SetScale(const DirectX::SimpleMath::Vector2& scale);
	const DirectX::SimpleMath::Vector2& GetScale() { return m_scale; }

	const DirectX::SimpleMath::Vector2& GetInialScale() { return m_initialScale; }

	void SetPosition(const DirectX::SimpleMath::Vector2& position);
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }

	const DirectX::SimpleMath::Vector2& GetInitialPosition() { return m_initialPosition; }

	void SetRenderRatio(const float& ratio);
	float GetRenderRatio() const { return m_renderRatio; }

	void SetRenderRatioOffset(const float& offset) { m_renderRatioOffset = offset; };
	float GetRenderRatioOffset() const { return m_renderRatioOffset; }

	void SetAlphaValue(const float& value) { m_alphaValue = value; }
	float GetAlphaValue() const { return m_alphaValue; }

	void SetIsActive(const bool& isActive) { m_isActive = isActive; }

	bool GetIsActive() const { return m_isActive; }

	int GetWidth() const { return m_textureWidth; }
	int GetHeight() const { return m_textureHeight; }


	void SetOffSetPosition(const DirectX::SimpleMath::Vector2& offsetPostion) { m_offsetPosition = offsetPostion; }

	//関数
public:
	//コンストラク
	DrawNumber();
	//デストラクタ
	~DrawNumber();
	//画像の読み込み
	void LoadTexture(const wchar_t* path);
	//生成
	void Create(DX::DeviceResources* pDR
		, const wchar_t* path
		, const DirectX::SimpleMath::Vector2& position
		, const DirectX::SimpleMath::Vector2& scale
		);
	//描画
	void Render(const int& number , const DirectX::SimpleMath::Vector2& offsetPosition);


private:
	//シェーダーの作成
	void CreateUIShader();



	//変数
private:
	DX::DeviceResources* m_pDR;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	//画像サイズ
	int m_textureWidth, m_textureHeight;
	//大きさ
	DirectX::SimpleMath::Vector2 m_scale;
	//座標
	DirectX::SimpleMath::Vector2 m_position;
	//初期座標
	DirectX::SimpleMath::Vector2 m_initialPosition;
	//初期の大きさ
	DirectX::SimpleMath::Vector2 m_initialScale;

	float m_renderRatio;
	//
	float m_renderRatioOffset;

	//画像全体の透明度
	float m_alphaValue;

	bool m_isActive;

	DirectX::SimpleMath::Vector2 m_offsetPosition;

};
