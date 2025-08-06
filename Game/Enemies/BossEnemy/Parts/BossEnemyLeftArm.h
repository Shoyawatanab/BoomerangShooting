/*
	クラス名     : BossEnemyLeftArm
	説明         : ボス敵の左腕モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;
class SoundComponent;

class BossEnemyLeftArm : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftArm";

public:
	//コンストラクタ
	BossEnemyLeftArm(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyLeftArm() override;

	//個別の当たった時の関数
	void OnCollisionEnterActor(ColliderComponent* collider);

private:

	//ヒット音
	SoundComponent* m_hitSE;



};