#pragma once
#include "GameBase/Actor.h"
#include "GameBase//Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Canvas;
class Image;


class BoomerangCount : public Actor , public IObserver<SceneMessageType>
{

	//UI全体の大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 0.1f,0.1f,0.0f };
	//UI全体の座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 180.0f,650.0f,0.0f };
	//オフセット
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION = { 120.0f,0.0f,0.0f };
	//ブーメランUI単体の大きさ
	static constexpr DirectX::SimpleMath::Vector3 BOOMERANG_SCALE = { 0.1f,0.1f,1.0f };

	

public:
	//コンストラクタ
	BoomerangCount(Canvas* canvas);
	//デストラクタ
	~BoomerangCount() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas)  override;

private:

	std::vector<Image*> m_boomerangUI;

};
