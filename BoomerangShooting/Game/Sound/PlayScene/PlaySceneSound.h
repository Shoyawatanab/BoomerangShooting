#pragma once
#include "GameBase/Actor.h"

class SoundComponent;

class PlaySceneSound : public Actor
{
public:
	//コンストラク
	PlaySceneSound(Scene* scene);
	//デストラクタ
	~PlaySceneSound() override;

private:
	//BGM
	SoundComponent* m_bgm;

};

