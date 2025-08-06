/*
	クラス名     : PlayerUsually
	説明         : プレイヤの常に処理したもののクラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Interface/IState.h"
#include "Game/Messenger/Messengers.h"

class Player;
class RigidbodyComponent;
class CommonResources;

class PlayerUsually 
{


public:
	//コンストラクタ
	PlayerUsually(Player* player);
	//デストラクタ
	~PlayerUsually();
	// 更新する
	void Update(const float& deltatime) ;


	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);
	//入力時
	void OnInput(const DirectX::Keyboard::Keys& key);


private:
	//移動
	void Move(const float& deltatime);
	//回転
	void Rotate(const float& deltatime);
	//マウスホイールのチェック
	void CheckMouseWheel();

private:
	//共通リソース
	CommonResources* m_commonResources;
	//プレイヤ
	Player* m_player;
	//リジットボディー
	RigidbodyComponent* m_rigidbody;

	//移動量
	DirectX::SimpleMath::Vector3 m_moveDirection;
	//ブーメランを構えているか true: 構えている  false:構えていない
	bool m_isGetReady;

};