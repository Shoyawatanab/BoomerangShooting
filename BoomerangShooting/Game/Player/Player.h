#pragma once
#include"GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"

class PlayerStateMachine;
class PlaySceneCamera;
class RigidbodyComponent;
class PlayerModel;
class AnimatorComponent;
class PlayerUsually;
class TargetMarker;

class Player : public Actor
{
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

	TargetMarker* GetTargetMarker() { return m_targetMarker; }

	void SetTargetMarker(TargetMarker* targetMarker) { m_targetMarker = targetMarker; }



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

};