/*
	クラス名     : InformationBase
	説明         : セレクトシーンの右の情報のまとめクラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Button;

class InformationBase : public Actor
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 1000.0f, 360.0f, 0 };
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 1.0f, 1.0f, 0 };

public:
	//コンストラク
	InformationBase(Canvas* canvas);
	//デストラクタ
	~InformationBase() override;

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

	//ステージ
	std::vector<Actor*> m_stage;


};

