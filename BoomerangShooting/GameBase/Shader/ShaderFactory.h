#pragma once
#include "Libraries/WataLib/Singleton.h"



class ShaderFactory : public Singleton<ShaderFactory>
{
	friend class Singleton<ShaderFactory>;
public:
	//コンストラクタ
	ShaderFactory() = default;
	//デストラクタ
	~ShaderFactory() = default;

	//バーテックスシェーダーの作成
	Microsoft::WRL::ComPtr<ID3D11VertexShader> CreateVS(ID3D11Device* device,std::string fileName);
	//ピクセルシェーダーの作成
	Microsoft::WRL::ComPtr<ID3D11PixelShader> CreatePS(ID3D11Device* device, std::string fileName);
	//ジオメトリックシェーダーの作成
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> CreateGS(ID3D11Device* device, std::string fileName);
	//インプットレイアウトの作成
	Microsoft::WRL::ComPtr<ID3D11InputLayout> CreateInputLayout(ID3D11Device* device, const std::vector<D3D11_INPUT_ELEMENT_DESC> layout, std::string fileName);

private:

	


};
