/*
	@file	Shadow.h
	@brief	影ポリゴンを表示するクラス
*/
#pragma once



namespace WataLib
{
	class Shadow
	{

	public:
		//コンストラクタ
		Shadow();
		//デストラクタ
		~Shadow() = default;

		// 初期化する
		void Initialize(
			ID3D11Device* device,
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states
		);

		// 描画する
		void Render(
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& projection,
			const DirectX::SimpleMath::Vector3& position,
			float radius = 0.7f
		);

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


	};
}