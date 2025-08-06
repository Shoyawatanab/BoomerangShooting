/*
	クラス名     : BossEnemyRightArm
	説明         : ボス敵の右腕モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;
class SoundComponent;

class BossEnemyRightArm : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightArm";

public:
	//コンストラクタ
	BossEnemyRightArm(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyRightArm() override;


	//個別の当たった時の関数
	void OnCollisionEnterActor(ColliderComponent* collider);

private:

	//ヒット音
	SoundComponent* m_hitSE;


};