/*
	クラス名     : BossEnemy
	説明         : ボス敵
	補足・注意点 :
*/
#pragma once
#include"Game/Enemies/EnemyBase.h"

class BossBehaviorTree;
class Player;
class RigidbodyComponent;
class AnimatorComponent;
class BossEnemyModel;
class BossEnemyActionManager;
class SoundComponent;


class BossEnemy : public EnemyBase 
{
public:

	enum  class ActionType
	{
		IDEL           //通常
		,BEAM_ATTACK   //ビーム攻撃
		,JUMP_ATTACK   //ジャンプ攻撃
		,ORIENTATION   //回転
		,SWINGDOWN	   //振り下ろし攻撃
		,WALK		   //歩き
	};


public:

	//着地しているか　true　着地してる　false　してない
	bool GetIsGround() const { return m_isGround; }


	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BOSS_ENEMY; }
	//アニメーションの取得
	AnimatorComponent* GetAnimation() { return m_animation; }
	//実行アクションタイプの取得
	ActionType GetCurrentActionType() { return m_currentActionType; }
	//実行アクションタイプのセット
	void SetCurrentActionType(ActionType type) { m_currentActionType = type; }

public:

	//コンストラクタ
	BossEnemy(Scene* scene , DirectX::SimpleMath::Vector3 scale
		,DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotation
		, EnemyManager* manager,Player* player);
	//デストラクタ
	~BossEnemy() override;

	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider) override;

	//当たり続けているときの呼び出される
	void OnCollisionStay(ColliderComponent* collider) override;

	//衝突が終了したときに呼び出される
	void OnCollisionExit(ColliderComponent* collider) override;

	//ダメージを食らったとき
	void AddDamage(int damage);

	//回転
	void Rotation(const float& deltaTime);

	//着地音の再生
	void PlayLandingSE();

private:

	//着地したとき
	void Landing();

private:

	//ビヘイビアツリー
	std::unique_ptr<BossBehaviorTree> m_behavior;


	//重力
	RigidbodyComponent* m_rigidBody;
	//アニメーション
	AnimatorComponent* m_animation;
	//アクションマネージャー
	std::unique_ptr<BossEnemyActionManager> m_actionManager;
	//着地しているか
	bool m_isGround;
	//プレイヤ
	Player* m_player;

	//着地音
	SoundComponent* m_landingSE;

	//アクション状態
	ActionType m_currentActionType;

};


