#include "pch.h"
#include "BossEnemyBeamRays.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Shader/ShaderFactory.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/Common/Commons.h"

//インプットレイアウト
const std::vector<D3D11_INPUT_ELEMENT_DESC> BossEnemyBeamRays::INPUT_LAYOUT =
{
	{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


/// <summary>
/// コンストラク
/// </summary>
/// <param name="sccene"></param>
BossEnemyBeamRays::BossEnemyBeamRays(Scene* scene)
	:
	Actor(scene)
{

	//コンポーネントの追加
	//外枠モデル
	m_outSidemodel = AddComponent<ModelComponent>(this, "Beam");
	m_outSidemodel->SetCustomRenderFunction(std::bind(&BossEnemyBeamRays::OutSideModelRender, this, std::placeholders::_1));
	//内側もです
	m_model = AddComponent<ModelComponent>(this, "Beam");
	m_model->SetCustomRenderFunction(std::bind(&BossEnemyBeamRays::ModelRender, this, std::placeholders::_1));

	//シェーダー作成
	CreateShader();

	SetActive(false);

}


/// <summary>
/// デストラクタ
/// </summary>
BossEnemyBeamRays::~BossEnemyBeamRays()
{
}

void BossEnemyBeamRays::ModelRender(const Camera& camera)
{

	using namespace DirectX::SimpleMath;

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();

	Vector4 color = Vector4(1, 1, 1, 1);

	auto model = m_model->GetModel();

	auto view = camera.GetViewMatrix();

	auto projection = camera.GetProjectionMatrix();

	//モデルを描画する
	model->Draw(context, *states, GetTransform()->GetWorldMatrix(),
		view, projection, false, [&]()
		{

			ConstBuffer cbuff;
			cbuff.matWorld = GetTransform()->GetWorldMatrix().Transpose();

			cbuff.matView = view.Transpose();
			cbuff.matProj = projection.Transpose();
			cbuff.Color = color;

			context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

			ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
			context->VSSetConstantBuffers(0, 1, cb);
			context->PSSetConstantBuffers(0, 1, cb);

			context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

			////	深度バッファに書き込み参照する
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			////	カリングはなし
			context->RSSetState(states->CullCounterClockwise());


			context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_pixelShader.Get(), nullptr, 0);


			context->IASetInputLayout(m_inputLayout.Get());
		});

}

void BossEnemyBeamRays::OutSideModelRender(const Camera& camera)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();


	Vector3 scale = GetTransform()->GetScale();
	scale.y *= 1.1f;
	scale.x *= 1.1f;


	//少し大きいマトリックスの作成
	DirectX::SimpleMath::Matrix world = Matrix::CreateScale(scale);
	world *= Matrix::CreateFromQuaternion(GetTransform()->GetRotate());
	world *= Matrix::CreateTranslation(GetTransform()->GetPosition());
	//親があれば
	if (GetTransform()->GetParent())
	{
		world *= GetTransform()->GetParent()->GetWorldMatrix();
	}


	Vector4 color = Vector4(1, 0, 0, 1);

	auto model = m_outSidemodel->GetModel();

	auto view = camera.GetViewMatrix();

	auto projection = camera.GetProjectionMatrix();


	//モデルを描画する
	model->Draw(context, *states, world, view, projection, false, [&]()
		{

			ConstBuffer cbuff;
			cbuff.matWorld = world.Transpose();

			cbuff.matView = view.Transpose();
			cbuff.matProj = projection.Transpose();
			cbuff.Color = color;

			context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

			ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
			context->VSSetConstantBuffers(0, 1, cb);
			context->PSSetConstantBuffers(0, 1, cb);

			context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

			////	深度バッファに書き込み参照する
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			////	カリングはなし
			context->RSSetState(states->CullClockwise());


			context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_pixelShader.Get(), nullptr, 0);


			context->IASetInputLayout(m_inputLayout.Get());

		});
}

void BossEnemyBeamRays::CreateShader()
{

	//シェーダーの作成
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();


	auto shaderFactory = ShaderFactory::GetInstance();

	//各シェーダーの作成
	m_vertexShader = shaderFactory->CreateVS(device, "BeamRaysVS.cso");
	m_pixelShader = shaderFactory->CreatePS(device, "BeamRaysPS.cso");

	m_inputLayout = shaderFactory->CreateInputLayout(device, INPUT_LAYOUT, "BeamRaysVS.cso");


	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	device->CreateBuffer(&bd, nullptr, &m_CBuffer);



}
