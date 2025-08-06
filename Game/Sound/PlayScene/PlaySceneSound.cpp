/*
	クラス名     : PlaySceneSound
	説明         : プレイシーンの音
	補足・注意点 :
*/
#include "pch.h"
#include "PlaySceneSound.h"
#include "Game/Component/Components.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
PlaySceneSound::PlaySceneSound(Scene* scene)
	:
	Actor(scene)
{

	std::string BGMName ="Stage1";

	switch (GlobalGameData::GetInstance()->GetSelectStateNumber())
	{
		case 1:
			BGMName = "Stage1";
			break;
		case 2:
			BGMName = "Stage2";
			break;
		default:
			break;
	}

	//BGMの作成
	m_bgm = AddComponent<SoundComponent>(this, BGMName, SoundComponent::SoundType::BGM);
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
