#pragma once
#include "GameBase/Actor.h"

class Camera;
class ModelComponent;

class BossEnemyBeamEnergyBall : public Actor
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

	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BEAM; }



public:
	//コンストラク
	BossEnemyBeamEnergyBall(Scene* scene);
	//デストラクタ
	~BossEnemyBeamEnergyBall();

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider) override;

	//アクティブになった時に呼ばれる関数
	void OnEnable() override;

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
