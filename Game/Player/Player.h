/*
	クラス名     : Player
	説明         : プレイヤ
	補足・注意点 :
*/
#pragma once
#include"GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class PlayerStateMachine;
class PlaySceneCamera;
class RigidbodyComponent;
class PlayerModel;
class AnimatorComponent;
class PlayerUsually;
class TargetMarker;
class PickerComponent;

class Player : public Actor
{
public:

	//投げ方
	enum class BoomerangThrowState : int
	{
		LEFT = -1           //左投げ　　この数字を使用してブーメランの回転の基準点を変更している
		,RIGHT = 1			//右投げ
	};

public:

	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::PLAYER; }

	//モデルの取得
	PlayerModel* GetPlayerModel() { return m_model; }
	//着地しているか　true　着地してる　false　してない
	bool GetIsGround() const { return m_isGround; }

	//プレイシーンカメラの取得
	PlaySceneCamera* GetPlaySceneCamera() { return m_playSceneCamera; }
	//プレイシーンカメラのセット
	void SetPlaySceneCamera(PlaySceneCamera* camera) { m_playSceneCamera = camera; }
	//ターゲットマーカーの取得
	TargetMarker* GetTargetMarker() { return m_targetMarker; }
	//ターゲットマーカーのセット
	void SetTargetMarker(TargetMarker* targetMarker) { m_targetMarker = targetMarker; }
	//ブーメランの投げの状態の取得
	BoomerangThrowState GetBoomerangThrowState() { return m_throwState; }


public:
	//コンストラクタ
	Player(Scene* scene);
	//デストラクタ
	~Player() override ;
	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider) override;

	//当たり続けているときの呼び出される
	void OnCollisionStay(ColliderComponent* collider) override;

	//衝突が終了したときに呼び出される
	void OnCollisionExit(ColliderComponent* collider) override;

	//武器が回収できるようになった
	void WeaponRecoverable();
	//武器が回収できなくなったとき
	void WeaponUnrecoverable();

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) ;


private:
	//着地したとき
	void Landing();
	//ダメージを食らったとき
	void AddDamage();

private:
	//ステートマシン
	std::unique_ptr<PlayerStateMachine>  m_stateMachine;
	//プレイシーンカメラ
	PlaySceneCamera* m_playSceneCamera;
	//重力
	RigidbodyComponent* m_rigidBody;
	//プレイヤモデル
	PlayerModel* m_model;
	//アニメーション
	AnimatorComponent* m_animation;
	//常に行う処理クラス
	std::unique_ptr<PlayerUsually> m_usually;
	//着地しているか
	bool m_isGround;
	//1フレ前の座標
	DirectX::SimpleMath::Vector3 m_lastPosition;
	//ターゲットマーカー
	TargetMarker* m_targetMarker;
	//HP
	int m_hp;
	//回収者コンポーネント
	PickerComponent* m_picker;
	//ブーメランの投げの状態
	BoomerangThrowState m_throwState;


};