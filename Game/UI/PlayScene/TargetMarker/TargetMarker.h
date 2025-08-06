/*
	クラス名     : TargetMarker
	説明         : ブーメランを投げるときのターゲットマーカーUI
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;

class TargetMarker : public Actor
{
public:
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE {0.3f, 0.3f, 200.0f};
	//ターゲットの中心からの距離
	static constexpr float RANGE{ 200.0f };
public:

	//構えているか true:LockOn状態   false:じゃない
	bool GetIsGetLockOn() { return m_isLockOn; }
	//ターゲット座標の取得
	DirectX::SimpleMath::Vector3 GetTargetPosition() { return m_targetPosition; }
	
public:
	//コンストラクタ
	TargetMarker(Canvas* canvas,std::vector<Actor*> targets);
	//デストラクタ
	~TargetMarker() override;
	// 単体更新
	void UpdateActor(const float& deltaTime) override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas);


private:
	//範囲内かどうかさがす
	DirectX::SimpleMath::Vector2 FilterWithinRange();


private:
	//マーカー
	Image* m_marker;
	//ターゲット配列
	std::vector<Actor*> m_targets;
	//
	DirectX::SimpleMath::Vector3 m_targetPosition;
	//構えているか
	bool m_isGetReady;
	//ロックオン状態か
	bool m_isLockOn;

};