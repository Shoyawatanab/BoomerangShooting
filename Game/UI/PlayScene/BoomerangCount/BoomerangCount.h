/*
	クラス名     : BoomerangCount
	説明         : ブーメランの投げれる数のUI
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;


class BoomerangCount : public Actor 
{

	//UI全体の大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 1.0f,1.0f,0.0f };
	//UI全体の座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 180.0f,650.0f,0.0f };
	//オフセット
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION = { 120.0f,0.0f,0.0f };
	//ブーメランUI単体の大きさ
	static constexpr DirectX::SimpleMath::Vector3 BOOMERANG_SCALE = { 0.2f,0.2f,1.0f };

	

public:
	//コンストラクタ
	BoomerangCount(Canvas* canvas);
	//デストラクタ
	~BoomerangCount() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);

private:

	std::vector<Image*> m_boomerangUI;

};
