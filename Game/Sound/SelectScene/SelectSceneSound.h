/*
	クラス名     : SelectSceneSound
	説明         : プレイシーンの音
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class SoundComponent;

class SelectSceneSound : public Actor
{
public:
	//コンストラク
	SelectSceneSound(Scene* scene);
	//デストラクタ
	~SelectSceneSound() override;

private:
	//BGM
	SoundComponent* m_bgm;

};

