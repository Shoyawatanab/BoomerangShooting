#pragma once
#include "GameBase/Actor.h"

class Canvas;
class NumberUI;
class Image;

class DamageCount : public Actor
{
public:

	//背景の大きさ
	static constexpr DirectX::SimpleMath::Vector3 BACKGROUND_SCALE = { 0.1f,0.1f,0.0f };
	//表示間隔
	static constexpr float SPACING = 20.0f;
	//最大表示桁
	static constexpr int MAXDIGITS = 3;

	//表示時間
	static constexpr float DISPLAYTIME = 0.5f;

public:
	//コンストラクタ
	DamageCount(Canvas* canvas);
	//デストラクタ
	~DamageCount() override;
	// 単体更新
	void UpdateActor(const float& deltaTime);

	//アクティブになった時に呼ばれる関数
	void OnEnable() override;
	//非アクティブになった時に呼ばれる関数
	void OnDisable() override;

	//ダメージのセット
	void SetDamage(int damage);

private:
	//時間
	float m_time;
	//背景
	Image* m_backGraund;
	//保存配列　最大桁数だけ所持
	std::vector<NumberUI*> m_numbers;
	//使用配列
	std::vector<NumberUI*> m_usedNumbers;
};