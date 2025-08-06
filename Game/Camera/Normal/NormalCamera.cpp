/*
	クラス名    :NormalCamera
	説明        : 初期カメラ
	補足・注意点:
*/
#include "pch.h"
#include "NormalCamera.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene"></param>
NormalCamera::NormalCamera(Scene* scene)
	:
	Camera(scene)	
{
}

/// <summary>
/// デストラクタ
/// </summary>
NormalCamera::~NormalCamera()
{
}


