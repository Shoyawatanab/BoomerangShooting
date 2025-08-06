/*
	クラス名     : FadeManager
	説明         : フェードマネージャー
	補足・注意点 :
*/
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
	,m_delayTime{}
{
	
	//フェードインの作成
	AddFadeIn(FadeInKinds::NORMAL_FADE_IN,std::make_unique<NormalFadeIn>());
	AddFadeIn(FadeInKinds::BOMERANG_FADE_IN,std::make_unique<BoomerangFadeIn>());

	//フェードアウトの作成
	AddFadeOut(FadeOutKinds::NORMAL_FADE_OUT, std::make_unique<NormalFadeOut>());
	AddFadeOut(FadeOutKinds::BOMERANG_FADE_OUT, std::make_unique<BoomerangFadeOut>());



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
	if (!m_isFade)
	{
		return;
	}

	//フェードが終わったかどうかのフラグ
	auto isEnd = false;

	switch (m_fadeState)
	{
		case FadeManager::FadeState::NONE:
			break;		
		case FadeManager::FadeState::DELAY:
			isEnd = DelayUpdate(deltaTime);
			break;
		case FadeManager::FadeState::FADE_IN:
		case FadeManager::FadeState::FADE_OUT:
			isEnd = m_currentFade->Update(deltaTime);
			break;
		default:
			break;
	}
	
	//終わったら
	if (isEnd)
	{
		switch (m_fadeState)
		{
			case FadeManager::FadeState::FADE_IN:
				m_fadeState = FadeState::DELAY;
				break;
			case FadeState::DELAY:
				m_fadeState = FadeState::NONE;
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
	if (!m_isFade)
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

	//データの切り替え
	ChangeFadeInDatas(kinds);
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

	//データの切り替え
	ChangeFadeInDatas(FadeInKinds::NORMAL_FADE_IN);

}

void FadeManager::StartFadeOut(FadeOutKinds kinds)
{

	//フェードインじゃないなら
	if (m_fadeState != FadeState::NONE)
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

	//データの切り替え
	ChangeFadeOutDatas(kinds);

}

void FadeManager::StartFadeOut()
{

	//フェードインじゃないなら
	if (m_fadeState != FadeState::NONE)
	{
		return;
	}

	//データの切り替え
	ChangeFadeOutDatas(FadeOutKinds::NORMAL_FADE_OUT);

}


/// <summary>
/// ディレイの更新
/// </summary>
/// <param name="deltaTime">経過時間</param>
/// <returns>true :終了 false:実行中</returns>
bool FadeManager::DelayUpdate(const float& deltaTime)
{

	m_delayTime += deltaTime;

	return m_delayTime >= DELAY_TIME;

}


/// <summary>
/// フェードイン状態のデータの切り替え
/// </summary>
/// <param name="kinds">フェードインの種類</param>
void FadeManager::ChangeFadeInDatas(FadeInKinds kinds)
{
	//実行フェードの切り替え
	ChangeFade(m_fadeInList[kinds].get());
	//
	m_fadeState = FadeState::FADE_IN;
	m_isFade = true;
}

/// <summary>
/// フェードアウト状態のデータの切り替え
/// </summary>
/// <param name="kinds">フェードアウトの種類</param>
void FadeManager::ChangeFadeOutDatas(FadeOutKinds kinds)
{
	//実行フェードの切り替え
	ChangeFade(m_fadeOutList[kinds].get());

	//
	m_fadeState = FadeState::FADE_OUT;
	m_isFade = true;
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
	//変更前のステートが存在する場合
	if (m_currentFade)
	{
		m_currentFade->Exit();
	}
	m_currentFade = fade;
	m_currentFade->Enter();
}







