/*
	クラス名     : BoomerangFadeOut
	説明         : ブーメラン型のフェードアウト
	補足・注意点 :
*/
#include "pch.h"
#include "BoomerangFadeOut.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/GameResources.h"
#include "Game/Fade/EasingFunctions.h"



///	<summary>
///	インプットレイアウト
///	</summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> BoomerangFadeOut::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


/// <summary>
/// コンストラク
/// </summary>
BoomerangFadeOut::BoomerangFadeOut()
	:
	m_batch{}
	,m_totalTime{}
{
	//シェーダーの作成
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	CreateShader();

	// フェードテクスチャの取得
	m_texture = GameResources::GetInstance()->GetTexture("fade");
	// 型抜きテクスチャの取得
	m_stencilImage = GameResources::GetInstance()->GetTexture("mask");
	// シェーダーの生成
	CreateShader();
	// プリミティブバッチの生成
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);
	// コモンステートの生成
	m_states = std::make_unique<DirectX::CommonStates>(device);

}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangFadeOut::~BoomerangFadeOut()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
/// <returns>true：終了　false：実行中</returns>
bool BoomerangFadeOut::Update(const float& deltaTime)
{
	
	m_totalTime += deltaTime;

	// 時間を計算する( 0 → 1 )
	m_totalTime = std::min(m_totalTime, FADE_TIME);

	return m_totalTime >= FADE_TIME;
}

/// <summary>
/// 描画
/// </summary>
void BoomerangFadeOut::Render()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DrawStencilImage();

	float easing = 0.0f;
	easing = std::max(0.0f, 1.0f - (m_totalTime / FADE_TIME));
	easing = std::max(0.0001f, Easing::easeInCubic(easing));

	ID3D11DeviceContext1* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(SimpleMath::Vector3(0.0f, 0.0f, 0.0f),SimpleMath::Vector4::One, SimpleMath::Vector2(0.0f, 0.0f)),
	};

	// シェーダーに渡す情報の媒体を作成する
	ConstBuffer cbuff;

	// 渡すデータを登録する
	cbuff.matView = SimpleMath::Matrix::Identity;				// スクリーン座標で描画するため不要
	cbuff.matProj = SimpleMath::Matrix::Identity;				// スクリーン座標で描画するため不要
	cbuff.matWorld = SimpleMath::Matrix::Identity;				// スクリーン座標で描画するため不要
	cbuff.Diffuse = SimpleMath::Vector4::One;					// テクスチャの色
	cbuff.time = SimpleMath::Vector4(easing, 0.0f, 0.0f, 0.0f);	// フェードの時間（第一要素のみ使用）


	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// シェーダーにバッファを渡す
	ID3D11Buffer* ccb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, ccb);
	context->GSSetConstantBuffers(0, 1, ccb);
	context->PSSetConstantBuffers(0, 1, ccb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//	半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	//	透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	//	カリングは正面のみ行う
	context->RSSetState(m_states->CullCounterClockwise());

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	// マスク画像をピクセルシェーダに登録する
	context->PSSetShaderResources(1, 1, m_captureSRV.GetAddressOf());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンで描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

void BoomerangFadeOut::Enter()
{
	m_totalTime = 0.0f;
}

void BoomerangFadeOut::Exit()
{

}



void BoomerangFadeOut::CreateShader()
{
	// デバイスの取得
	ID3D11Device* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

//マスク以外のシェーダーの作成
	auto shaderFactory = ShaderFactory::GetInstance();
	//各シェーダーの作成
	m_vertexShader = shaderFactory->CreateVS(device, "DieCuttingVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "DieCuttingPS.cso");
	m_geometryShader = shaderFactory->CreateGS(device, "DieCuttingGS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "DieCuttingVS.cso");



//マスク用のシェーダーの作成

		//各シェーダーの作成
	m_maskVS = shaderFactory->CreateVS(device, "MaskVS.cso");
	m_maskPS = shaderFactory->CreatePS(device, "MaskPS.cso");
	m_maskGS = shaderFactory->CreateGS(device, "MaskGS.cso");

	m_maskInputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "MaskVS.cso");

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);


}

float BoomerangFadeOut::CalcrateFadeValue(float easing)
{
	return Easing::easeBetweenOut(easing, FADE_THRESHOLD, FADE_FIRST_SIZE, FADE_MAX_SIZE);
}

void BoomerangFadeOut::DrawStencilImage()
{
	// デバイスリソースの取得
	auto deviceResources = CommonResources::GetInstance()->GetDeviceResources();
	// コンテキストの取得
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

	//	描画についての設定を行う
	D3D11_TEXTURE2D_DESC texDesc;
	deviceResources->GetRenderTarget()->GetDesc(&texDesc);
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	deviceResources->GetD3DDevice()->CreateTexture2D(&texDesc, NULL, m_capture.ReleaseAndGetAddressOf());

	//	レンダーターゲットビューの設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	//	レンダーターゲットビューの生成
	deviceResources->GetD3DDevice()->CreateRenderTargetView(m_capture.Get(), &rtvDesc, &m_captureRTV);

	//	シェーダリソースビューの設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	//	レンダーターゲットビューと深度ビューを取得（後で元に戻すため）
	ID3D11RenderTargetView* defaultRTV = deviceResources->GetRenderTargetView();
	ID3D11DepthStencilView* pDSV = deviceResources->GetDepthStencilView();

	// 背景色の取得(透明)
	float backColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// レンダーターゲットと深度ステンシルの設定
	context->OMSetRenderTargets(1, m_captureRTV.GetAddressOf(), pDSV);
	context->ClearRenderTargetView(m_captureRTV.Get(), backColor);
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// フェードの時間を 0 ~ 1で正規化させる
	float t = m_totalTime / FADE_TIME;
	// フェードのサイズを計算
	float size = CalcrateFadeValue(t);

	DirectX::SimpleMath::Matrix world;
	world = DirectX::SimpleMath::Matrix::CreateScale(size, size, 1.0f);

	// シェーダーに渡す情報の媒体を作成する
	ConstBuffer cbuff;

	// 渡すデータを登録する
	cbuff.matView = DirectX::SimpleMath::Matrix::Identity;						// スクリーン座標で描画するため不要
	cbuff.matProj = DirectX::SimpleMath::Matrix::Identity;						// スクリーン座標で描画するため不要
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4::One;							// テクスチャの色
	cbuff.time = DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f);				// フェードの時間（第一要素のみ使用）

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// シェーダーにバッファを渡す
	ID3D11Buffer* ccb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, ccb);
	context->GSSetConstantBuffers(0, 1, ccb);
	context->PSSetConstantBuffers(0, 1, ccb);

	//	画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	描画するオブジェクトの情報を設定
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),DirectX::SimpleMath::Vector4::One, DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_stencilImage.GetAddressOf());

	//	シェーダをセットする
	context->VSSetShader(m_maskVS.Get(), nullptr, 0);
	context->GSSetShader(m_maskGS.Get(), nullptr, 0);
	context->PSSetShader(m_maskPS.Get(), nullptr, 0);

	//	インプットレイアウトの登録
	context->IASetInputLayout(m_maskInputLayout.Get());

	// (実際には表示しないが) 描画を行う
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	描画した画面をcaptureSRVに保存する
	deviceResources->GetD3DDevice()->CreateShaderResourceView
	(
		m_capture.Get(), &srvDesc, m_captureSRV.ReleaseAndGetAddressOf()
	);

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

	//	保持しておいたデフォルト設定に戻して、画面描画が正常に出来るようにしておく
	context->OMSetRenderTargets(1, &defaultRTV, pDSV);
	// 使用した物を解放
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 0.0f, 0);

}
