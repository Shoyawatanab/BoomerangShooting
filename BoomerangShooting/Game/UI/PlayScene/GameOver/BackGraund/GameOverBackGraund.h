#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class GameOverBackGraund : public Image
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


public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{640, 360, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.1f, 0.1f, 0};
	//アニメーション時間
	static constexpr float ANIMATION_TIME = 4.0f;
public:

	//アニメーション終了時に有効にするオブジェクト
	void SetActor(std::vector<Actor*> actor) { m_actor = actor; }

public:
	//コンストラク
	GameOverBackGraund(Canvas* canvas);
	//デストラクタ
	~GameOverBackGraund() override;

	// 単体更新
	void UpdateActor(const float& deltaTime) override;

	//アクティブになった時に呼ばれる関数
	void OnEnable() override;

private:

	//描画
	void CustomRender();

	//シェーダー作成
	void CreateShader(ID3D11Device1* device, ID3D11DeviceContext* context);
	
	//画像の読み込み
	void LoadTexture();

private:
	//画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
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

	//アニメーションが終わった後に有効にするActor
	std::vector<Actor*> m_actor;


};

