#pragma once
#include "GameBase/Actor.h"


class Camera;
class ModelComponent;

class BossEnemyBeamRays : public Actor
{
public:
	//コンスタントバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    Color;

	};

public:
	//コンストラク
	BossEnemyBeamRays(Scene* scene);
	//デストラクタ
	~BossEnemyBeamRays();

private:
	//内枠描画
	void ModelRender(const Camera& camera);
	//外枠描画
	void OutSideModelRender(const Camera& camera);
	//シェーダー作成
	void CreateShader();

private:
	//インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;


	//モデルコンポーネント
	ModelComponent* m_outSidemodel;
	ModelComponent* m_model;


};


