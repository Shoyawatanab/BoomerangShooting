/*
	クラス名     : TitleButton
	説明         : ゲームオーバーUI
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;
class Button;
class GameOverBackGraund;


class GameOverUI : public Actor
{
public:
	//コンストラク
	GameOverUI(Canvas* canvas);
	//デストラクタ
	~GameOverUI() override;

	//アクティブになった時に呼ばれる関数
	void OnEnable() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:
	//背景
	GameOverBackGraund* m_backGraund;
	//
	Button* m_retryButton;
	//
	Button* m_titleButton;
};


