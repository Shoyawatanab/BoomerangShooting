/*
	クラス名     : TitleSceneSound
	説明         : タイトルシーンの音
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class SoundComponent;

class TitleSceneSound : public Actor
{
public:
	//コンストラク
	TitleSceneSound(Scene* scene);
	//デストラクタ
	~TitleSceneSound() override;

private:
	//BGM
	SoundComponent* m_bgm;

};

