/*
	クラス名     : SelectSceneSound
	説明         : タイトルシーンの音
	補足・注意点 :
*/
#include "pch.h"
#include "SelectSceneSound.h"
#include "Game/Component/Components.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
SelectSceneSound::SelectSceneSound(Scene* scene)
	:
	Actor(scene)
{

	//BGMの作成
	m_bgm = AddComponent<SoundComponent>(this, "StageSelect", SoundComponent::SoundType::BGM);
	//再生
	//m_bgm->Play();



}

/// <summary>
/// デストラクタ
/// </summary>
SelectSceneSound::~SelectSceneSound()
{
	//BGMの停止
	m_bgm->Stop();
}
