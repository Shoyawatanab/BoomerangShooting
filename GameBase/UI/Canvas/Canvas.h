/*
	クラス名     : Canvas
	説明         : UIキャンバスの基底クラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class Canvas : public Actor
{
public:

	enum  class RenderType
	{
	
		SpaceOverlay  //常に画面に移り続ける
		, WorldSpace  //３D空間のオブジェクトとして配置
	};



public:

	//コンストラクタ
	Canvas(Scene * scene, RenderType type);
	//デストラクタ
	~Canvas();

private:
	//描画の種類
	RenderType m_type;

};




