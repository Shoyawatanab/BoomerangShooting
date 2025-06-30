#include "pch.h"
#include "PlaySceneScreenSpaceOverlayCanvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/PlayScene/PlaySceneUIs.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
PlaySceneScreenSpaceOverlayCanvas::PlaySceneScreenSpaceOverlayCanvas(Scene* scene, std::vector<Actor*> targets)
	:
	ScreenSpaceOverlayCanvas(scene)
	,m_targetMarker{}
{

	//PlyerHpの作成
	auto playerHp = GetScene()->AddActor<PlayerHp>(this);

	m_targetMarker = GetScene()->AddActor<TargetMarker>(this,targets);

	GetScene()->AddActor<BoomerangCount>(this);

	GetScene()->AddActor<DamageCountFactory>(this);

	GetScene()->AddActor<BossHp>(this);

	GetScene()->AddActor<PlayerDamageEffect>(this);

	GetScene()->AddActor<GameOverUI>(this);

}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneScreenSpaceOverlayCanvas::~PlaySceneScreenSpaceOverlayCanvas()
{
}



