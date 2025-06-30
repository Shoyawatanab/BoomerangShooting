#pragma once
#include <unordered_map>

#include "Libraries/WataLib/Singleton.h"



namespace FMOD
{
	class Sound;
	class System;
}


class GameResources : public Singleton<GameResources>
{
	friend class Singleton<GameResources>;
	// ------------------------
	// ファイルパス
	// ------------------------
public:
	// モデルのJsonファイル
	static const wchar_t* MODEL_JSON;
	static const wchar_t* MODEL_BASE_PATH;

	// テクスチャのJsonファイル
	static const wchar_t* TEXTURE_JSON;
	static const wchar_t* TEXTURE_BASE_PATH;

public:

	// モデルを取得する
	DirectX::Model* GetModel(std::string key) const;
	// テクスチャを取得する
	ID3D11ShaderResourceView* GetTexture(std::string key) const;

public:
	// コンストラクタ
	GameResources();
	// デストラクタ
	~GameResources() = default;

private:
	// Jsonファイルを読み込んでモデルを生成する
	void LoadModelFromJson(ID3D11Device1* device);

	// テクスチャを読み込む
	void LoadTexture(ID3D11Device1* device);



private:


	// モデルリスト
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> m_modelList;

	// テクスチャリスト
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textureList;

	std::unordered_map<std::string, FMOD::Sound*> m_soundList;

};




