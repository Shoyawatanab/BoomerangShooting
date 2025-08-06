/*
	クラス名     : StageFactory
	説明         : ステージ作成クラス
	補足・注意点 :
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