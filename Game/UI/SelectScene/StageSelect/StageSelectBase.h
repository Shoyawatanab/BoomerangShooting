/*
	クラス名     : StageSelectBase
	説明         : セレクトシーンのステージUIのまとめクラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Messengers.h"

class Image;
class Canvas;


class StageSelectBase : public Actor 
{
public:

	//最大ステージ数
	static constexpr int MAX_STAGE_COUNT = 2;

public:
	//コンストラクタ
	StageSelectBase(Canvas* canvas);
	//デストラクタ
	~StageSelectBase() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:

	//ステージ番号UIの切り替え
	void ChangeStageUI(int stateNumber);

private:
	//選択中のステージ番号
	int m_selectStageNumber;
	//描画しているステージ番号
	int m_drawStageNumber;

	//ステージUI　１から順番に入れるようにする
	std::vector<Image*> m_stageUI;

};

