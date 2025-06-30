#pragma once
#include "GameBase/Actor.h"

class Camera;
class ParticleUtility;


class Particle : public Actor
{
public:
	//コンスタントバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};


public:
	//インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//生成間隔
	static constexpr float GENERATION_INTERVAL = 0.5f;
	//生成時間
	static constexpr float GENERATION_TIME = 1.5f;
	//ユーティリティの数
	static constexpr int UTILITY_COUNT = 20;
	//生成半径
	static constexpr float GENERATE_RADIUS = 3.0f;



public:
	//コンストラク
	Particle(Scene* scene);
	//デストラクタ
	~Particle() override;

	// コンポーネント全体の更新
	void UpdateActor(const float& deltaTime) override;

	//描画処理
	void Render(const Camera& camera);

	//アクティブになった時に呼ばれる関数
	void OnEnable() override;

	//エフェクトの作成
	void Create();

private:

	//シェーダーの作成
	void CreateShader();
	//ユーティリティの作成
	void CreateUtility();


private:
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	//	テクスチャハンドル
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//	ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	//ビルボード行列
	DirectX::SimpleMath::Matrix m_billboard;
	//頂点情報
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	//ユーティリティクラス
	std::vector<ParticleUtility> m_ChargeEffectUtility;
	//時間
	float m_time;
	//ユーティリティクラス
	std::vector<ParticleUtility> m_particleUtility;



};
