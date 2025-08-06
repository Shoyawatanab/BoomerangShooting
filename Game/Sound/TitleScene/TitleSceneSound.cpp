/*
	クラス名     : TitleSceneSound
	説明         : タイトルシーンの音
	補足・注意点 :
*/
#include "pch.h"
#include "TitleSceneSound.h"
#include "Game/Component/Components.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
TitleSceneSound::TitleSceneSound(Scene* scene)
	:
	Actor(scene)
{

	//BGMの作成
	m_bgm = AddComponent<SoundComponent>(this, "Title", SoundComponent::SoundType::BGM);
	//再生
	m_bgm->Play();



}

/// <summary>
/// デストラクタ
/// </summary>
TitleSceneSound::~TitleSceneSound()
{
	//BGMの停止
	m_bgm->Stop();
}
