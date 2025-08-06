/*
	クラス名     : ResultTime
	説明         : リザルトシーンの時間UI
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class Canvas;
class NumberUI;
class TimeSeparator;

class ResultTime : public Actor
{
public:

	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 1.0f,1.0f,1.0f };
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 750,310,0 };
	//文字間隔
	static constexpr float LETTER_SPACING = 100.0f;
	//点滅間隔
	static constexpr float BLINK_INTERVAL = 1.0f;


public:
	//コンストラク
	ResultTime(Canvas* canvas);
	//デストラクタ
	~ResultTime() override;

	//個別アップデート
	void UpdateActor(const float& deltaTime) override;


	//時間のセット
	void AddTime(const float& totalSecond);

private:

	//点滅
	void Blink(const float& deltaTime);
	
private:

	//数字配列
	std::vector<NumberUI*> m_numbers;
	//区切り点
	TimeSeparator* m_separator;

	//時間
	float m_time;


};