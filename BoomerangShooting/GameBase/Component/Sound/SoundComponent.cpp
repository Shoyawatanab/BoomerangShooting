#include "pch.h"
#include "SoundComponent.h"
#include "GameBase/Manager/SoundManager.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="soundName">サウンド名</param>
/// <param name="type">再生の種類</param>
SoundComponent::SoundComponent(Actor* owner, const std::string& soundName, SoundType type)
	:
	Component(owner)
	,m_channelSE{}
	,m_soundType{}
	,m_sound{}
	,m_manager{}
{

	//マネージャーの取得
	m_manager = SoundManager::GetInstance();
	//マネージャーの作成
	m_manager->MakeSound(soundName,type,&m_sound);

}

/// <summary>
/// デストラクタ
/// </summary>
SoundComponent::~SoundComponent()
{
}

/// <summary>
/// 再生
/// </summary>
void SoundComponent::Play()
{

	switch (m_soundType)
	{
		case SoundComponent::SoundType::BGM:
			//BGMの再生
			m_manager->PlayBGM(&m_sound);
			break;
		case SoundComponent::SoundType::SE:
			//SEの再生
			m_manager->PlaySE(&m_sound, &m_channelSE);
			break;
		default:
			break;
	}

}

/// <summary>
/// 停止
/// </summary>
void SoundComponent::Stop()
{

	switch (m_soundType)
	{
		case SoundComponent::SoundType::BGM:
			m_manager->StopBGM(&m_sound);
			break;
		case SoundComponent::SoundType::SE:
			break;
		default:
			break;
	}

}
