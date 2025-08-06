/*
	クラス名     : SelectSceneCamera
	説明         : セレクトシーンカメラ
	補足・注意点 :
*/
#pragma once
#include "GameBase/Camera/Camera.h"

class SelectSceneCamera : public Camera
{
public:
	//コンストラク
	SelectSceneCamera(Scene* scene);
	//デストラクタ
	~SelectSceneCamera() override;



private:


};