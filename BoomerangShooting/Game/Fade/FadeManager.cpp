#include "pch.h"
#include "FadeManager.h"
#include "Game/Fade/FadeKindss.h"



/// <summary>
/// コンストラク
/// </summary>
FadeManager::FadeManager()
	:
	m_currentFade{}
	,m_fadeState{FadeState::NONE}
	, m_fadeInList{}
	,m_fadeOutList{}
	, m_isFade{ false }
{
	
	//フェードインの作成
	AddFadeIn(FadeInKinds::NORMAL_FADE_IN,std::make_unique<NormalFadeIn>());
	
	//フェードアウトの作成
	AddFadeOut(FadeOutKinds::NORMAL_FADE_OUT, std::make_unique<NormalFadeOut>());



}

/// <summary>
/// デストラクタ
/// </summary>
FadeManager::~FadeManager()
{
	
	m_fadeInList.clear();
	m_fadeOutList.clear();
	
}

/// <summary>
/// 
/// </summary>
/// <param name="deltaTime"></param>
void FadeManager::Update(const float& deltaTime)
{
	//実行中でないなら
	if (m_fadeState == FadeState::NONE)
	{
		return;
	}

	//フェードの更新
	auto isEnd = m_currentFade->Update(deltaTime);
	
	//終わったら
	if (isEnd)
	{
		switch (m_fadeState)
		{
			case FadeManager::FadeState::FADE_IN:
				m_fadeState = FadeState::FADE_IN_END;
				break;
			case FadeManager::FadeState::FADE_OUT:
				m_isFade = false;
				m_fadeState = FadeState::NONE;
				break;
			default:
				break;
		}
	}

}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera"></param>
void FadeManager::Render()
{

	//実行中でないなら
	if (m_fadeState == FadeState::NONE)
	{
		return;
	}

	m_currentFade->Render();

}


/// <summary>
/// フェードのスタート
/// </summary>
/// <param name="startFade">実行フェード</param>
void FadeManager::StartFadeIn(FadeInKinds kinds)
{
	//フェードが実行されていないなら
	if (m_fadeState != FadeState::NONE)
	{
		return;
	}

	//あるか
	auto it = m_fadeInList.find(kinds);
	//なければ
	if (it == m_fadeInList.end())
	{
		return;
	}

	//実行フェードの切り替え
	ChangeFade(m_fadeInList[kinds].get());
	//状態の変更
	m_fadeState = FadeState::FADE_IN;
	m_isFade = true;
}

/// <summary>
/// フェードのスタート　ノーマルフェード
/// </summary>
void FadeManager::StartFadeIn()
{
	//フェードが実行されていないなら
	if (m_fadeState != FadeState::NONE)
	{
		return;
	}

	//実行フェードの切り替え
	ChangeFade(m_fadeInList[FadeInKinds::NORMAL_FADE_IN].get());
	//
	m_fadeState = FadeState::FADE_IN;

	m_isFade = true;

}

void FadeManager::StartFadeOut(FadeOutKinds kinds)
{

	//フェードインじゃないなら
	if (m_fadeState != FadeState::FADE_IN_END)
	{
		return;
	}

	//あるか
	auto it = m_fadeOutList.find(kinds);
	//なければ
	if (it == m_fadeOutList.end())
	{
		return;
	}

	//実行フェードの切り替え
	ChangeFade(m_fadeOutList[kinds].get());
	//状態の変更
	m_fadeState = FadeState::FADE_OUT;

}

void FadeManager::StartFadeOut()
{

	//フェードインじゃないなら
	if (m_fadeState != FadeState::FADE_IN_END)
	{
		return;
	}

	//実行フェードの切り替え
	ChangeFade(m_fadeOutList[FadeOutKinds::NORMAL_FADE_OUT].get());

	//
	m_fadeState = FadeState::FADE_OUT;
}

/// <summary>
/// フェードインの追加
/// </summary>
/// <param name="kinds">フェードの種類</param>
/// <param name="fade">フェードクラス</param>
void FadeManager::AddFadeIn(FadeInKinds kinds, std::unique_ptr<IFade> fade)
{

	m_fadeInList[kinds] = std::move(fade);

}

/// <summary>
/// フェードアウトの追加
/// </summary>
/// <param name="kinds">フェードの種類</param>
/// <param name="fade">フェードクラス</param>
void FadeManager::AddFadeOut(FadeOutKinds kinds, std::unique_ptr<IFade> fade)
{

	m_fadeOutList[kinds] = std::move(fade);

}



/// <summary>
/// フェードの切り替え
/// </summary>
/// <param name="fade">切り替え先フェード</param>
void FadeManager::ChangeFade(IFade* fade)
{
	if (m_currentFade)
	{
		m_currentFade->Exit();
	}
	m_currentFade = fade;
	m_currentFade->Enter();
}





