#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Canvas;
class Image;

class PlayerHp : public Actor , public IObserver<SceneMessageType>
{
public:

	//UI全体の大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 1.0f,1.0f,0.0f };
	//UI全体の座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 180.0f,550.0f,0.0f };
	//オフセット
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION = { 120.0f,0.0f,0.0f };
	//ハートの大きさ
	static constexpr DirectX::SimpleMath::Vector3 HEART_SCALE = { 0.5f,0.5f,100.4f };

public:
	//コンストラクタ
	PlayerHp(Canvas* canvas);
	//デストラクタ
	~PlayerHp() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) override;


private:

	std::vector<Image*> m_heart;

};