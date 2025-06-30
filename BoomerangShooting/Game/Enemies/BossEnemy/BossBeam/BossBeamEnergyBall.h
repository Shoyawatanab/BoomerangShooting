/*
	@file	BossBeamEnergyBall.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "GameBase/Actor.h"

// 前方宣言
class CommonResources;
class Beam;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class Bounding;

}

class BossBeamEnergyBall : public Actor
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

	static constexpr DirectX::SimpleMath::Vector3 INITALPOSITION { 100, 100, 0 };


public:
	//コンストラク
	BossBeamEnergyBall(Scene* scene);
	
	//デストラクタ
	~BossBeamEnergyBall() override;

	
	//初期化
	void Initialize() override;




	//リセット
	void ReSet();

private:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;



	// モデル
	DirectX::Model* m_model;
	//初期回転
	DirectX::SimpleMath::Quaternion m_initialRotate;
	//ターゲット
	DirectX::SimpleMath::Vector3 m_target;
	//初期サイズ
	DirectX::SimpleMath::Vector3 m_initialScale;
	//最大サイズ
	DirectX::SimpleMath::Vector3 m_maxScale;
	//最大サイズになる時間
	float m_maxSizeTime;
	//時間
	float m_time;




};
