#pragma once
#include "GameBase/Component.h"

class SoundManager;

namespace FMOD
{
	class System;
	class Sound;
	class Channel;
}

class SoundComponent : public Component
{
public:
	//再生の種類
	enum class SoundType : int
	{
		BGM = 0
		,SE 
	};

public:
	//コンストラクタ
	SoundComponent(Actor* owner,const std::string& soundName,SoundType type);
	//デストラクタ
	~SoundComponent() override;

	//再生
	void Play();
	//停止
	void Stop();

private:
	//マネージャー
	SoundManager* m_manager;

	//再生の種類
	SoundType m_soundType;
	//サウンド
	FMOD::Sound* m_sound;
	//SEチャンネル
	FMOD::Channel* m_channelSE;

};

