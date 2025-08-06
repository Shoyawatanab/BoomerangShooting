/*
	クラス名     : BossJumpAttackActionController
	説明         : ボス敵のジャンプ攻撃のコントローラー
	補足・注意点 :
*/
#pragma once
#include "GameBase/Action/ActionController.h"
#include "GameBase/Actor.h"

#include "Game/Enemies/BossEnemy/Action/JumpAttack/BossJumpAttackCharge.h"
#include "Game/Enemies/BossEnemy/Action/JumpAttack/BossJumpAttackJump.h"
#include "Game/Enemies/BossEnemy/Action/Orientation/OrientationAction.h"


// 前方宣言
class CommonResources;
class Player;
class BossEnemy;



class BossJumpAttackActionController : public ActionController 
{

public:
	//ジャンプ力
	static  constexpr float JUMPPOWER = 0.3f;
	//動きのスピード
	static  constexpr float MOVESPEED = 9.0f;

public:

	//ジャンプ方向の取得
	const DirectX::SimpleMath::Vector3& GetJumpDirection() { return m_jumpDirection; }
	//ジャンプ方向のセット
	void SetJumpDirection(const DirectX::SimpleMath::Vector3& direction) { m_jumpDirection = direction; }

public:
	//コンストラクタ
	BossJumpAttackActionController(BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossJumpAttackActionController()override;




private:
	// 共通リソース
	CommonResources* m_commonResources;

	//チャージ
	std::unique_ptr<BossJumpAttackCharge> m_charge;
	//ジャンプ
	std::unique_ptr<BossJumpAttackJump> m_jump;
	//回転
	std::unique_ptr<OrientationAction> m_orientation;
	
	//ジャンプ方向
	DirectX::SimpleMath::Vector3 m_jumpDirection;

};
