/*
	クラス名     : FadeManager
	説明         : フェードマネージャー
	補足・注意点 :
*/
#pragma once
#include "GameBase/WataLib/Singleton.h"
#include "Game/Fade/IFade.h"

class Camera;
class IFade;
class NormalFade;

class FadeManager : public Singleton<FadeManager>
{
	friend class Singleton<FadeManager>;

public:
	//フェードの状態
	enum class FadeState
	{
		NONE                //通常
		,FADE_IN    	    //フェードイン
		,DELAY              //ディレイ
		,FADE_OUT		    //フェードアウト
	};

	//フェードインの種類
	enum  class FadeInKinds
	{
		NORMAL_FADE_IN                 //ノーマルフェードイン
		,BOMERANG_FADE_IN
	};
	//フェードアウトの種類
	enum  class FadeOutKinds
	{

		NORMAL_FADE_OUT			   //ノーマルフェードアウト
		,BOMERANG_FADE_OUT

	};



	//ディレイ時間
	static constexpr float DELAY_TIME = 0.5f;

public:

	//フェード状態の取得
	FadeState GetFadeState() { return m_fadeState; }
	//フェード実行中かの取得　true：実行中　false：未実行
	bool GetIsFade() const { return m_isFade; }



public:
	//コンストラク
	FadeManager();
	//デストラクタ
	~FadeManager() override;
	//更新処理
	void Update(const float& deltaTime);
	//描画
	void Render();
	//フェードインのスタート
	void StartFadeIn(FadeInKinds kinds);
	//フェードインのスタート　ノーマルフェード
	void StartFadeIn();
	//フェードアウトのスタート
	void StartFadeOut(FadeOutKinds kinds);
	//フェードアウトのスタート　ノーマルフェード
	void StartFadeOut();

private:
	//ディレイの更新
	bool DelayUpdate(const float& deltaTime);
	//フェードイン状態のデータの切り替え
	void ChangeFadeInDatas(FadeInKinds kinds);
	//フェードイン状態のデータの切り替え
	void ChangeFadeOutDatas(FadeOutKinds kinds);
	//フェードインの追加
	void AddFadeIn(FadeInKinds kinds, std::unique_ptr<IFade> fade);
	//フェードアウトの追加
	void AddFadeOut(FadeOutKinds kinds, std::unique_ptr<IFade> fade);
	//フェードの切り替え
	void ChangeFade(IFade* fade);

private:
	//実行フェーズ
	IFade* m_currentFade;
	//フェード状態
	FadeState m_fadeState;

	//フェードイン配列
	std::unordered_map<FadeInKinds, std::unique_ptr<IFade>> m_fadeInList;
	//フェードアウト配列
	std::unordered_map<FadeOutKinds, std::unique_ptr<IFade>> m_fadeOutList;
	//フェード実行中か　true：実行中　false：未実行
	bool m_isFade;
	//ディレイ時間
	float m_delayTime;

};




