/*
	クラス名     : Canvas
	説明         : UIキャンバスの基底クラス
	補足・注意点 :
*/
#include "pch.h"
#include "Canvas.h"

Canvas::Canvas(Scene* scene, RenderType type)
	:
	Actor(scene)
	,m_type{type}
{
}

Canvas::~Canvas()
{
}
