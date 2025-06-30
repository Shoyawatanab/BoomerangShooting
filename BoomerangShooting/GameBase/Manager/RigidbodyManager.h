#pragma once
#include "GameBase/Component/Rigidbody/RigidbodyComponent.h"


class RigidbodyManager
{

public:
	//コンストラクタ
	RigidbodyManager();
	//デストラクタ
	~RigidbodyManager();

	//更新処理
	void Update(const float& deltaTime);
	//リジットボディーの追加
	void AddRigidbody(RigidbodyComponent* rigidbody);
	//リジットボディーの削除
	void RemoveRigidbody(RigidbodyComponent* rigidbody);

private:
	//リジットボディーコンポーネント
	std::vector<RigidbodyComponent*> m_rigidbody;

};