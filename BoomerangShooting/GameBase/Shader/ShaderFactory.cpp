#include "pch.h"
#include "ShaderFactory.h"
#include "Libraries/MyLib/BinaryFile.h"


/// <summary>
/// バーテックスシェーダーの作成
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="fileName">ファイル名</param>
/// <returns>バーテックスシェーダー</returns>
Microsoft::WRL::ComPtr<ID3D11VertexShader> ShaderFactory::CreateVS(ID3D11Device* device, std::string fileName)
{
	//ファイルパスの作成
	std::string filePath = "Resources/Shaders/" + fileName;
	//stringをwstringに変換
	std::wstring wfile(filePath.begin(), filePath.end());
	//const wchar_tに変換
	const wchar_t* wfilePath = wfile.c_str();

	//バーテックスシェーダーのデータの読み込み
	 BinaryFile VSDatas = BinaryFile::LoadFile(wfilePath);
	//バーテックスシェーダーの格納変数
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;

	//	頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSDatas.GetData(), VSDatas.GetSize(), NULL, vertexShader.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return nullptr;
	}

	return vertexShader;
}


/// <summary>
/// ピクセルシェーダーの作成
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="fileName">ファイル名</param>
/// <returns>ピクセルシェーダー</returns>
Microsoft::WRL::ComPtr<ID3D11PixelShader> ShaderFactory::CreatePS(ID3D11Device* device, std::string fileName)
{
	//ファイルパスの作成
	std::string filePath = "Resources/Shaders/" + fileName;
	//stringをwstringに変換
	std::wstring wfile(filePath.begin(), filePath.end());
	//const wchar_tに変換
	const wchar_t* wfilePath = wfile.c_str();

	//ピクセルシェーダーのデータの読み込み
	BinaryFile PSDatas = BinaryFile::LoadFile(wfilePath);
	//ピクセルシェーダーの格納変数
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;

	//	ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSDatas.GetData(), PSDatas.GetSize(), NULL, pixelShader.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return nullptr;
	}

	return pixelShader;

}

/// <summary>
/// ジオメトリシェーダーの作成
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="fileName">ファイル名</param>
/// <returns>ジオメトリシェーダー</returns>
Microsoft::WRL::ComPtr<ID3D11GeometryShader> ShaderFactory::CreateGS(ID3D11Device* device, std::string fileName)
{
	//ファイルパスの作成
	std::string filePath = "Resources/Shaders/" + fileName;
	//stringをwstringに変換
	std::wstring wfile(filePath.begin(), filePath.end());
	//const wchar_tに変換
	const wchar_t* wfilePath = wfile.c_str();

	//ジオメトリシェーダーのデータの読み込み
	BinaryFile GSDatas = BinaryFile::LoadFile(wfilePath);
	//ジオメトリシェーダーの格納変数
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> geometryShader;

	//	ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSDatas.GetData(), GSDatas.GetSize(), NULL, geometryShader.ReleaseAndGetAddressOf())))
	{//	エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return nullptr;
	}

	return geometryShader;
}

Microsoft::WRL::ComPtr<ID3D11InputLayout> ShaderFactory::CreateInputLayout(ID3D11Device* device, const std::vector<D3D11_INPUT_ELEMENT_DESC> layout, std::string fileName)
{
	

	//ファイルパスの作成
	std::string filePath = "Resources/Shaders/" + fileName;
	//stringをwstringに変換
	std::wstring wfile(filePath.begin(), filePath.end());
	//const wchar_tに変換
	const wchar_t* wfilePath = wfile.c_str();

	//バーテックスシェーダーのデータの読み込み
	BinaryFile VSDatas = BinaryFile::LoadFile(wfilePath);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

	//インプットレイアウトの作成
	device->CreateInputLayout(&layout[0],
		static_cast<UINT>(layout.size()),
		VSDatas.GetData(), VSDatas.GetSize(),
		inputLayout.GetAddressOf());

	return inputLayout;

}
