/*
	クラス名     : Sky
	説明         : 天球
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class Camera;
class ModelComponent;

class Sky : public Actor
{
public:
	//コンストラク
	Sky(Scene* scene);
	//デストラクタ
	~Sky() override;

private:

	void Render(const Camera& camera);

private:
	//モデルコンポーネント
	ModelComponent* m_modelComponent;


};
