#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Component/UI/ImageComponent.h"

class Canvas;
class ImageComponent;

class Image : public Actor
{
public:

	//切り取り範囲のセット
	void SetCutRange(DirectX::SimpleMath::Vector4 range) { m_imageComponent->SetCutRange(range); }
	//色のセット
	void SetColor(DirectX::SimpleMath::Vector4 color) { m_imageComponent->SetColor(color); }

	//横の塗りつぶし量　０～１までの範囲
	void SetHorizontalFillAmount(float fillAmount) { m_imageComponent->SetHorizontalFillAmount(fillAmount); }
	//カスタム描画関数の登録
	void SetCustomRenderFunction(std::function<void()> customRender) { m_imageComponent->SetCustomRenderFunction(customRender); }

public:

	//コンストラクタ
	Image(Canvas* canvas, const std::string& textureName);
	//デストラクタ
	~Image();

private:

	ImageComponent* m_imageComponent;


};