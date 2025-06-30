#include "pch.h"
#include "SoundManager.h"
#include "Libraries/FMOD/inc/fmod.hpp"
#include "Libraries/FMOD/inc/fmod_errors.h"
#include <fstream>
#include "nlohmann/json.hpp"


//サウンドのJsonファイル
const wchar_t* SoundManager::SOUND_JSON = L"Resources//Dates/SoundData.json";
const char* SoundManager::SOUND_BASE_PATH = "Resources/Sounds/";


/// <summary>
/// コンストラク
/// </summary>
SoundManager::SoundManager()
	:
	m_channelBGM{}
	,m_soundPathList{}
	,m_system{}
{

	// システムをインスタンス化する
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	//システムの初期化
	m_system->init(32, FMOD_INIT_NORMAL, nullptr);

	//音の読み込み
	LoadSound();


}


/// <summary>
/// デストラクタ
/// </summary>
SoundManager::~SoundManager()
{
	m_system->release();

}

/// <summary>
/// 更新処理
/// </summary>
void SoundManager::Update()
{
	m_system->update();

}


void SoundManager::MakeSound(const std::string& soundName, SoundComponent::SoundType type, FMOD::Sound** sound)
{

	auto soundPath = m_soundPathList.find(soundName);

	//なければ
	if (soundPath == m_soundPathList.end())
	{
		return;
	}

	switch (type)
	{
		case SoundComponent::SoundType::BGM:
			//ループ再生
			m_system->createSound(soundPath->second.c_str(), FMOD_LOOP_NORMAL, nullptr, sound);
			break;
		case SoundComponent::SoundType::SE:
			//1回だけ再生
			m_system->createSound(soundPath->second.c_str(), FMOD_DEFAULT, nullptr, sound);

			break;
		default:
			break;
	}




}

/// <summary>
/// BGMの再生
/// </summary>
/// <param name="sound"></param>
void SoundManager::PlayBGM(FMOD::Sound** sound)
{
	// 現在のBGMが再生中なら止める
	if (m_channelBGM)
	{
		bool isPlaying = false;
		m_channelBGM->isPlaying(&isPlaying);
		//再生中なら止める
		if (isPlaying)
		{
			m_channelBGM->stop();
		}
	}

	m_system->playSound((*sound), nullptr, false, &m_channelBGM);


}


/// <summary>
/// SEの再生
/// </summary>
/// <param name="sound"></param>
/// <param name="Channel"></param>
void SoundManager::PlaySE(FMOD::Sound** sound, FMOD::Channel** channel)
{
	bool isPlaying;
	//再生状態の取得
	(*channel)->getPaused(&isPlaying);

	//再生中なら
	if (isPlaying)
	{
		//初めに戻す
		(*channel)->setPosition(0, FMOD_TIMEUNIT_MS);
		//再生
		m_system->playSound((*sound), nullptr, false, channel);

	}


}

/// <summary>
/// BGMの停止
/// </summary>
/// <param name="sound"></param>
void SoundManager::StopBGM(FMOD::Sound** sound)
{

	m_channelBGM->stop();

}


void SoundManager::LoadSound()
{
	//Jsonファイルを開く
	std::ifstream ifs(SOUND_JSON);

	if (!ifs)
	{
		MessageBoxA(nullptr, "SoundJsonファイルが見つかりません", "エラー", MB_OK);
		return; // 処理を終了
	}

	// Jsonファイルを読み込む
	nlohmann::json json = nlohmann::json::parse(ifs);


	FMOD::System* system;
	// システムをインスタンス化する
	FMOD_RESULT result = FMOD::System_Create(&system);
	// システムを初期化する
	system->init(32, FMOD_INIT_NORMAL, nullptr);
	//BGMの読み込み
	for (const auto& bgmDatas : json["BGM"])
	{
		for (auto it = bgmDatas.begin(); it != bgmDatas.end(); ++it)
		{
			// キーと値を取得
			std::string key = it.key();
			std::string pathStr = it.value();
			// std::stringをstd::wstringに変換
			std::string path = SOUND_BASE_PATH + std::string(pathStr.begin(), pathStr.end());
			//リストに保存
			m_soundPathList[key] = path;

		}

	}


	//SEの読み込み
	for (const auto& bgmDatas : json["SE"])
	{

		for (auto it = bgmDatas.begin(); it != bgmDatas.end(); ++it)
		{

			// キーと値を取得
			std::string key = it.key();
			std::string pathStr = it.value();

			// std::stringをstd::wstringに変換
			std::string path = SOUND_BASE_PATH + std::string(pathStr.begin(), pathStr.end());
			//リストに保存
			m_soundPathList[key] = path;

		}

	}

}
