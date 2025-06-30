#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Image;
class Canvas;

class PlayerDamageEffect : public Actor , public IObserver<SceneMessageType>
{
public:

	//	関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//コンスタントバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	Time;
	};


public:
	//コンストラク
	PlayerDamageEffect(Canvas* canvas);
	//デストラクタ
	~PlayerDamageEffect() override ;
	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//カスタム描画
	void CustomRender();

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) override;


private:

	//シェーダー作成
	void CreateShader();
	//開始
	void Begin();

private:

	//コンストバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	//透明度
	float m_alpha;


	Image* m_image;

};

