/*
ステージ作成クラス
*/


#pragma once
#include "GameBase/Actor.h"

class StageFactory : public Actor
{
public:

	struct StageParameter
	{
		DirectX::SimpleMath::Vector3 Scale;
		DirectX::SimpleMath::Vector3 Position;
		DirectX::SimpleMath::Quaternion Rotation;
	};

public:
	//コンストラクタ
	StageFactory(Scene* scene);
	//デストラクタ
	~StageFactory() override ;

private:

	//ステージデータの読み込み
	void LoadStageData();

};