#include "pch.h"
#include "Image.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="canvas">キャンバス</param>
/// <param name="textureName">画像名</param>
Image::Image(Canvas* canvas, const std::string& textureName)
	:
	Actor(canvas->GetScene())
{

	//イメージの追加
	m_imageComponent = AddComponent<ImageComponent>(this, textureName);


}

/// <summary>
/// デストラクタ
/// </summary>
Image::~Image()
{
}
