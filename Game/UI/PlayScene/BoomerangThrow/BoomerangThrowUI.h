#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;

class BoomerangThrowUI :public Actor
{
public:
	//左投げUI
	//座標
	static constexpr DirectX::SimpleMath::Vector3 RIGHT_UI_POSITION ={1180, 550, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 RIGHT_UI_SCALE = { 0.3f, 0.3f, 0 };
	//右投げUI
	//座標
	static constexpr DirectX::SimpleMath::Vector3 LEFT_UI_POSITION = { 1180, 630, 0 };
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 LEFT_UI_SCALE = { 0.3f, 0.3f, 0 };

	//移動量
	static constexpr DirectX::SimpleMath::Vector3 OFFSET = { -50, 0, 0 };


public:
	//コンストラク
	BoomerangThrowUI(Canvas* canvas);
	//デストラクタ
	~BoomerangThrowUI();

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:
	//左投げ
	Image* m_leftThrow;
	//右投げ
	Image* m_rightThrow;

};