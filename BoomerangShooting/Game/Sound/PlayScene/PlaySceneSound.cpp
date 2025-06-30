#include "pch.h"
#include "PlaySceneSound.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
PlaySceneSound::PlaySceneSound(Scene* scene)
	:
	Actor(scene)
{
	//BGMの作成
	m_bgm = AddComponent<SoundComponent>(this, "Play", SoundComponent::SoundType::BGM);
	//再生
	m_bgm->Play();



}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneSound::~PlaySceneSound()
{
	//BGMの停止
	m_bgm->Stop();
}
