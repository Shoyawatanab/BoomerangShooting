//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2023/09/03
// <file>			Easing.cpp
// <概要>			イージング関数を扱う
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"easing.h"
#include<math.h>
#define M_PI        3.141592f


NakashiLib::Easing::Easing() {
	change = 0;
	change_amount = 0;
	turn = true;
}

NakashiLib::Easing::~Easing() {

}


/// <summary>
/// 数値変更処理
/// </summary>
void NakashiLib::Easing::Start(float speed, float strNum, float endNum) {
	change += speed;
	//変化量をセット
	change_amount = endNum - strNum;
	if (change >= 1.0f) {
		change = 1.0f;
	}
}

/// <summary>
/// 終了呼び出し処理
/// </summary>
bool NakashiLib::Easing::EndChange() {
	if (change >= 1.0f) {
		return true;
	}
	return false;
}

/// <summary>
/// リセット処理
/// </summary>
void NakashiLib::Easing::Reset() {
	change = 0;
}

/// <summary>
/// Normal
/// </summary>
float NakashiLib::Easing::Normal(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);

	return strNum + change_amount * change;
}


/// <summary>
/// Sine系統
/// </summary>
float NakashiLib::Easing::InSine(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(1 - cos((change * M_PI) / 2));
}

float NakashiLib::Easing::OutSine(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(sin((change * M_PI) / 2));
}

float NakashiLib::Easing::InOutSine(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(-(cos(M_PI * change) - 1) / 2);
}



/// <summary>
/// Quad系統
/// </summary>
float NakashiLib::Easing::InQuad(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change * change);
}

float NakashiLib::Easing::OutQuad(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(1 - (1 - change) * (1 - change));
}

float NakashiLib::Easing::InOutQuad(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change < 0.5 ? 2 * change * change :
														1 - pow(-2 * change + 2, 2) / 2);
}



/// <summary>
/// Qubic系統
/// </summary>
float NakashiLib::Easing::InQubic(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change * change * change);
}

float NakashiLib::Easing::OutQubic(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(1 - pow(1 - change, 3));
}

float NakashiLib::Easing::InOutQubic(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change < 0.5 ? 4 * change * change * change :
									1 - pow(-2 * change + 2, 3) / 2);
}

/// <summary>
/// Quart系統
/// </summary>
float NakashiLib::Easing::InQuart(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change * change * change * change);
}

float NakashiLib::Easing::OutQuart(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(1 - pow(1 - change, 4));
}

float NakashiLib::Easing::InOutQuart(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change < 0.5 ? 8 * change * change * change * change :
									1 - pow(-2 * change + 2, 4) / 2);
}




/// <summary>
/// Quint系統
/// </summary>
float NakashiLib::Easing::InQuint(float speed, float strNum, float endNum){
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(powf(change ,5));
}

float NakashiLib::Easing::OutQuint(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(1 - powf(1 - change,5));
}

float NakashiLib::Easing::InOutQuint(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change < 0.5 ? 16 * change * change * change * change * change :
									1 - pow(-2 * change + 2, 5) / 2);
}



/// <summary>
/// Expo系統
/// </summary>
float NakashiLib::Easing::InExpo(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change == 0 ? 0 : pow(2, 10 * change - 10));
}

float NakashiLib::Easing::OutExpo(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change == 1 ? 1 : 1 - pow(2, -10 * change));
}

float NakashiLib::Easing::InOutExpo(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change == 0
		? 0
		: change == 1
		? 1
		: change < 0.5 ? pow(2, 20 * change - 10) / 2
		: (2 - pow(2, -20 * change + 10)) / 2);
}



/// <summary>
/// Circ系統
/// </summary>
float NakashiLib::Easing::InCirc(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(1 - sqrt(1 - pow(change, 2)));
}

float NakashiLib::Easing::OutCirc(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(sqrt(1 - pow(change - 1, 2)));
}

float NakashiLib::Easing::InOutCirc(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	return strNum + change_amount * static_cast<float>(change < 0.5
		? (1 - sqrt(1 - pow(2 * change, 2))) / 2
		: (sqrt(1 - pow(-2 * change + 2, 2)) + 1) / 2);
}


/// <summary>
/// Back系統
/// </summary>
float NakashiLib::Easing::InBack(float speed, float strNum, float endNum){
	Start(speed, strNum, endNum);

	float c1 = 1.70158f;
	float c3 = c1 + 1;

	return  strNum + change_amount * static_cast<float>(c3 * change * change * change
														- c1 * change * change);
}

float NakashiLib::Easing::OutBack(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);

	float c1 = 1.70158f;
	float c3 = c1 + 1;

	return strNum + change_amount * static_cast<float>(1 + c3 * powf(change - 1, 3) + 
														c1 * powf(change - 1, 2));
}

float NakashiLib::Easing::InOutBack(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);

	float c1 = 1.70158f;
	float c2 = c1 * 1.525f;
	return strNum + change_amount * static_cast<float>(change < 0.5
		? (pow(2 * change, 2) * ((c2 + 1) * 2 * change - c2)) / 2
		: (pow(2 * change - 2, 2) * ((c2 + 1) * (change * 2 - 2) + c2) + 2) / 2);
}



/// <summary>
/// Elastic系統
/// </summary>
float NakashiLib::Easing::InElastic(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	float c4 = static_cast<float>(2 * M_PI) / 3;
	return strNum + change_amount * static_cast<float>(change == 0
		? 0
		: change == 1
		? 1
		: -pow(2, 10 * change - 10) * sin((change * 10 - 10.75) * c4));
}

float NakashiLib::Easing::OutElastic(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	float c4 = static_cast<float>(2 * M_PI) / 3;
	return strNum + change_amount * static_cast<float>(change == 0
		? 0
		: change == 1
		? 1
		: pow(2, -10 * change) * sin((change * 10 - 0.75) * c4) + 1);
}

float NakashiLib::Easing::InOutElastic(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	float c5 = static_cast<float>(2 * M_PI) / 4.5;
	return strNum + change_amount * static_cast<float>(change == 0
		? 0
		: change == 1
		? 1
		: change < 0.5
		? -(pow(2, 20 * change - 10) * sin((20 * change - 11.125) * c5)) / 2
		: (pow(2, -20 * change + 10) * sin((20 * change - 11.125) * c5)) / 2 + 1);
}





/// <summary>
/// Bounce系統
/// </summary>
float NakashiLib::Easing::InBounce(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	float n1 = 7.5625f;
	float d1 = 2.75f;
	float change2 = 1 - change;

	if (change2 < 1 / d1) {
		return strNum + change_amount * static_cast<float>(1 - (n1 * change2 * change2));
	}
	else if (change2 < 2 / d1) {
		return strNum + change_amount * static_cast<float>(1 -(n1 * pow((change2 - 1.5f / d1), 2) + 0.75f));
	}
	else if (change2 < 2.5 / d1) {
		return strNum + change_amount * static_cast<float>(1 -(n1 * pow((change2 - 2.25f / d1), 2) + 0.9375f));
	}
	else {
		return strNum + change_amount * static_cast<float>(1 - (n1 * pow((change2 - 2.625f / d1), 2) + 0.984375f));
	}
}


float NakashiLib::Easing::OutBounce(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	float n1 = 7.5625f;
	float d1 = 2.75f;

	if (change < 1 / d1) {
		return strNum + change_amount * static_cast<float>(n1 * change * change);
	}
	else if (change < 2 / d1) {
		return strNum + change_amount * static_cast<float>(n1 * pow((change - 1.5f / d1),2) + 0.75f);
	}
	else if (change < 2.5 / d1) {
		return strNum + change_amount * static_cast<float>(n1 * pow((change - 2.25f / d1),2) + 0.9375f);
	}
	else {
		return strNum + change_amount * static_cast<float>(n1 * pow((change - 2.625f / d1),2) + 0.984375f);
	}
}

float NakashiLib::Easing::InOutBounce(float speed, float strNum, float endNum) {
	Start(speed, strNum, endNum);
	float n1 = 7.5625f;
	float d1 = 2.75f;
	float change3 = 1 - 2 * change;
	float change4 = 2 * change - 1;
	float re1;
	if (change3 < 1 / d1) {
		re1 = strNum + change_amount * static_cast<float>((1 - (n1 * change3 * change3)) / 2);
	}
	else if (change3 < 2 / d1) {
		re1 = strNum + change_amount * static_cast<float>((1 - (n1 * pow((change3 - 1.5f / d1), 2) + 0.75f))/ 2);
	}
	else if (change3 < 2.5 / d1) {
		re1 = strNum + change_amount * static_cast<float>((1 - (n1 * pow((change3 - 2.25f / d1), 2) + 0.9375f))/ 2);
	}
	else {
		re1 = strNum + change_amount * static_cast<float>((1 - (n1 * pow((change3 - 2.625f / d1), 2) + 0.984375f)) / 2);
	}

	float re2;
	if (change4 < 1 / d1) {
		re2 = strNum + change_amount * static_cast<float>((1 + (n1 * change4 * change4)) / 2);
	}
	else if (change4 < 2 / d1) {
		re2 = strNum + change_amount * static_cast<float>((1 + (n1 * pow((change4 - 1.5f / d1), 2) + 0.75f)) / 2);
	}
	else if (change4 < 2.5 / d1) {
		re2 = strNum + change_amount * static_cast<float>((1 + (n1 * pow((change4 - 2.25f / d1), 2) + 0.9375f)) / 2);
	}
	else {
		re2 = strNum + change_amount * static_cast<float>((1 + (n1 * pow((change4 - 2.625f / d1), 2) + 0.984375f)) / 2);
	}

	return change < 0.5
		? re1
		: re2;
}


/// <summary>
/// イージング関数を選ぶ
/// </summary>
/// <param name="type">どのタイプ</param>
/// <param name="speed">速度</param>
/// <param name="strNum">スタートの値</param>
/// <param name="endNum">エンドの値</param>
float NakashiLib::Easing::Selection(EasingType type, float speed, float strNum, float endNum) {
	switch (type)
	{
		case Easing::EasingType::Nomal:
			return Normal(speed, strNum, endNum);
			break;
		case Easing::EasingType::InSine:
			return InSine(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutSine:
			return OutSine(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutSine:
			return InOutSine(speed, strNum, endNum);
			break;
		case Easing::EasingType::InQuad:
			return InQuad(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutQuad:
			return OutQuad(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutQuad:
			return InOutQuad(speed, strNum, endNum);
			break;
		case Easing::EasingType::InQubic:
			return InQubic(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutQubic:
			return OutQubic(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutQubic:
			return InOutQubic(speed, strNum, endNum);
			break;
		case Easing::EasingType::InQuart:
			return InQuart(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutQuart:
			return OutQuart(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutQuart:
			return InOutQuart(speed, strNum, endNum);
			break;
		case Easing::EasingType::InQuint:
			return InQuint(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutQuint:
			return OutQuint(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutQuint:
			return InOutQuint(speed, strNum, endNum);
			break;
		case Easing::EasingType::InExpo:
			return InExpo(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutExpo:
			return OutExpo(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutExpo:
			return InOutExpo(speed, strNum, endNum);
			break;
		case Easing::EasingType::InCirc:
			return InCirc(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutCirc:
			return OutCirc(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutCirc:
			return InOutCirc(speed, strNum, endNum);
			break;
		case Easing::EasingType::InBack:
			return InBack(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutBack:
			return OutBack(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutBack:
			return InOutBack(speed, strNum, endNum);
			break;
		case Easing::EasingType::InElastic:
			return InElastic(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutElastic:
			return OutElastic(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutElastic:
			return InOutElastic(speed, strNum, endNum);
			break;
		case Easing::EasingType::InBounce:
			return InBounce(speed, strNum, endNum);
			break;
		case Easing::EasingType::OutBounce:
			return OutBounce(speed, strNum, endNum);
			break;
		case Easing::EasingType::InOutBounce:
			return InOutBounce(speed, strNum, endNum);
			break;
		default:
			return 0;
			break;
	}
}


/// <summary>
/// ターンさせる
/// </summary>
/// <param name="type1">一つ目のタイプ</param>
/// <param name="type2">二つ目のタイプ</param>
/// <param name="speed">速度</param>
/// <param name="strNum">スタートの値</param>
/// <param name="endNum">エンドの値</param>
float NakashiLib::Easing::Turn(EasingType type1, EasingType type2, float speed, float strNum, float endNum)
{

	if (EndChange())
	{
		turn = !turn;
		Reset();
	}

	if (turn)
	{
		return Selection(type1, speed, strNum, endNum);
	}
	else {
		return Selection(type2, speed, endNum, strNum);
	}
}


float NakashiLib::Easing::Rope(EasingType type, float speed, float strNum, float endNum)
{
	if (EndChange())
	{
		Reset();
	}

	return Selection(type, speed, strNum, endNum);
}

