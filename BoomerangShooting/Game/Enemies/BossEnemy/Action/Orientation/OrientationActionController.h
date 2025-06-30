#pragma once
#include "GameBase/Action/ActionController.h"
#include "GameBase/Actor.h"

#include "Game/Enemies/BossEnemy/Action/Orientation/OrientationAction.h"


// 前方宣言
class CommonResources;
class Player;
class BossEnemy;



class OrientationActionController : public ActionController
{

public:



public:
	//コンストラクタ
	OrientationActionController(BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~OrientationActionController()override;




private:
	// 共通リソース
	CommonResources* m_commonResources;

	//回転
	std::unique_ptr<OrientationAction> m_orientation;


};
#pragma once
