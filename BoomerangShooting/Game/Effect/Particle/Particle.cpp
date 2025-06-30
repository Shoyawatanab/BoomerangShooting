#include "pch.h"
#include "Particle.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/GameResources.h"
#include "GameBase/Component/Components.h"
#include "Game/Effect/ParticleUtility.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "Game/MathUtil.h"

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> Particle::INPUT_LAYOUT =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                                                                           D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),                                        D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	     0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
Particle::Particle(Scene* scene)
	:
	Actor(scene)
	,m_inputLayout{}
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	AddComponent<EffectComponent>(this, std::bind(&Particle::Render, this, std::placeholders::_1));



	using namespace DirectX;

	//デバイスの取得
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	//コンテキストの取得
	ID3D11DeviceContext1* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	シェーダーの作成
	CreateShader();

	//画像の取得
	m_texture.push_back(GameResources::GetInstance()->GetTexture("da"));

	//	プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
	//コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	GetTransform()->SetScale(Vector3(10, 10, 10));

	SetActive(false);

}

/// <summary>
/// デストラクタ
/// </summary>
Particle::~Particle()
{
}

/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime">経過時間</param>
void Particle::UpdateActor(const float& deltaTime)
{

	//ユーティリティの更新
	for (auto it = m_particleUtility.begin(); it != m_particleUtility.end(); )
	{
		if (!it->Update(deltaTime)) {
			it = m_particleUtility.erase(it);  // 削除後の新しいイテレーターを取得
		}
		else {
			++it;  // 削除しなかった場合は次の要素へ
		}
	}

}



/// <summary>
/// 描画
/// </summary>
/// <param name="camera">カメラ</param>
void Particle::Render(const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//コンテキストの取得
	ID3D11DeviceContext1* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	auto view = camera.GetViewMatrix();
	auto projection = camera.GetProjectionMatrix();
	//	登録されている頂点をリセット
	m_vertices.clear();
	for (ParticleUtility& li : m_particleUtility)
	{
		VertexPositionColorTexture vPCT;
		//	表示するパーティクルの中心座標のみを入れる。
		//	→つまり、C++で用意しているデータだけではテクスチャを表示できない。
		//	　→ジオメトリシェーダを使う事前提のデータ、ということ
		vPCT.position = XMFLOAT3(li.GetPosition());
		//	テクスチャの色
		vPCT.color = XMFLOAT4(li.GetNowColor());
		//	現在のテクスチャのスケールを「XMFLOAT2」のXに入れる。
		//	Yは使っていないし、そもそものTextureのUV座標とは違う使い方になっていることに注意
		vPCT.textureCoordinate = XMFLOAT2(li.GetNowScale().x, 0.0f);

		m_vertices.push_back(vPCT);
	}

	//	表示する点がない場合は描画を終わる
	if (m_vertices.empty())
	{
		return;
	}


	// ビルボードマトリックスを計算する
	m_billboard = view.Invert();
	m_billboard._41 = 0.0f;
	m_billboard._42 = 0.0f;
	m_billboard._43 = 0.0f;

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = projection.Transpose();
	cbuff.matWorld = m_billboard.Transpose();
	cbuff.Diffuse = SimpleMath::Vector4(1, 1, 1, 1);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定		補間アルファ合成
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	//	カリングはなし
	context->RSSetState(m_states->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	指定した座標を中心に、シェーダ側で板ポリゴンを生成・描画させる
	m_batch->Begin();


	//	ジオメトリシェーダでPointを受け取ることになっているため、
	//	ここではD3D11_PRIMITIVE_TOPOLOGY_POINTLISTを使う
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);


}

/// <summary>
/// アクティブ状態になった時
/// </summary>
void Particle::OnEnable()
{
	m_time = 0.0f;
	Create(); 
}

//エフェクト作成
void Particle::Create()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	//パーティクルを作成
	for (int i = 0; i < UTILITY_COUNT; i++)
	{

		//	完全なランダムをハードウェア的に生成するためのクラスの変数
		std::random_device seed;
		//ランダムエンジン
		std::default_random_engine engine(seed());
		//ランダム範囲の指定
		std::uniform_real_distribution<> dist(0, XM_2PI);
		//角度の作成
		float angle = static_cast<float>(dist(engine));
		//ランダム範囲の指定
		std::uniform_real_distribution<> dist2(0.5f, 1.0f);
		//乱数の生成
		float speedY = static_cast<float>(dist2(engine) / 2.5f);
		float speedX = static_cast<float>(dist2(engine));

		//中心から放射状に広がる方向のベクトル
		Vector3 vectorFormCenter = Vector3(
			GENERATE_RADIUS * cosf(angle),
			0.0f,
			GENERATE_RADIUS * sinf(angle)
		);
		//中心からの距離を取得
		float distanceFormCenter = vectorFormCenter.Length();
		//正規化
		vectorFormCenter.Normalize();
		//中心からの距離に応じて速度を増加
		float scaleFactor = 2.0f + (distanceFormCenter / GENERATE_RADIUS);
		Vector3 adjustedVelocity = vectorFormCenter * scaleFactor;

		//負になるように反転
		Vector3 velocity = -adjustedVelocity;
		//初期座標
		Vector3 dustPos = GetTransform()->GetWorldPosition() + Vector3(
			GENERATE_RADIUS * cosf(angle),
			0.0f,
			GENERATE_RADIUS * sinf(angle)

		);


		//	0～2PIの値をdefault_random_engine(恐らくしばらくはmt19937)を使って取り出す
		ParticleUtility pU(
			1.0f,																			//	生存時間(s)
			dustPos,																		//	基準座標
			Vector3(-velocity.x * speedX, speedY, -velocity.z * speedX),					//	速度
			Vector3::Zero,																	//	加速度
			Vector3::One,																	//	初期スケール、
			Vector3(10, 10, 10),															//  最終スケール
			Color(1.f, 1.f, 1.f, 1.f),														//	初期カラー
			Color(1.f, 1.f, 1.f, -1.f)														//  最終カラー
		);
		//追加
		m_particleUtility.push_back(pU);
	}

}

void Particle::CreateShader()
{
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	auto shaderFactory = ShaderFactory::GetInstance();

	//各シェーダーの作成
	m_vertexShader = shaderFactory->CreateVS(device, "ParticleVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "ParticlePS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "ParticleGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "ParticleVS.cso");


	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);

}

void Particle::CreateUtility()
{

	using namespace DirectX::SimpleMath;

	int count = 12;
	float radius = 2.0f;
	Vector3 scale = Vector3(2, 2, 2);


	for (int i = 0; i < count; i++)
	{
		//角度を求める
		float angle = DirectX::XM_2PI * i / count;
		float x = radius * cos(angle);
		float z = radius * sin(angle);

		Vector3 pos = Vector3(x, 0.0f, z);

		Vector3 velocity = Vector3(cos(angle), 0.0f, sin(angle));

		ParticleUtility pU(
			3.0f,																			//	生存時間(s)
			pos + GetTransform()->GetWorldPosition(),				                                                        //	基準座標
			velocity,		//	速度
			Vector3(0.5f, 0.0f, 0.5f),														//	加速度
			scale,                                                      //	初期スケール
			scale,							                  //	最終スケール
			Color(1.f, 1.f, 1.f, 1.f),											// 初期カラー、
			Color(1.f, 1.f, 1.f, -1.f)										   //	最終カラー
		);

		m_ChargeEffectUtility.push_back(pU);
	}

}
