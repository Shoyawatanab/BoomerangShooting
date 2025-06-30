#pragma once
#include "Libraries/WataLib/Singleton.h"
#include "GameBase/Component/Sound/SoundComponent.h"

namespace FMOD
{
	class System;
	class Sound;
	class Channel;
}

class SoundManager : public Singleton<SoundManager>
{
public:
	//サウンドのJsonファイル
	static const wchar_t* SOUND_JSON;
	static const char* SOUND_BASE_PATH;

public:
	//コンストラク
	SoundManager();
	//デストラクタ
	~SoundManager() override;

	//更新処理
	void Update();

	//BGMの再生
	void PlayBGM(FMOD::Sound** sound);
	//SEの再生
	void PlaySE(FMOD::Sound** sound,FMOD::Channel** Channel);
	//BGMの停止
	void StopBGM(FMOD::Sound** sound);

	//サウンドの作成
	void MakeSound(const std::string& soundName, SoundComponent::SoundType type,FMOD::Sound** sound);

private:

	//データの読み込み
	void LoadSound();

private:

	//システム
	FMOD::System* m_system;
	//BGMチャンネル
	FMOD::Channel* m_channelBGM;
	//音のパスの保存リスト
	std::unordered_map<std::string, std::string> m_soundPathList;


};