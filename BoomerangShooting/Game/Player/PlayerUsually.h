/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "GameBase/Interface/IState.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Player;
class RigidbodyComponent;


class PlayerUsually : public IObserver<SceneMessageType>
{


public:
	//コンストラクタ
	PlayerUsually(Player* player);
	//デストラクタ
	~PlayerUsually();
	// 更新する
	void Update(const float& deltatime) ;


	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) override;


private:
	//移動
	void Move(const float& deltatime);
	//回転
	void Rotate(const float& deltatime);
private:
	//プレイヤ
	Player* m_player;
	//リジットボディー
	RigidbodyComponent* m_rigidbody;

	//移動量
	DirectX::SimpleMath::Vector3 m_moveDirection;
	//ブーメランを構えているか true: 構えている  false:構えていない
	bool m_isGetReady;

};