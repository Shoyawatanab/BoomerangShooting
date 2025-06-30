//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2023/09/03
// <file>			Easing.h
// <概要>			イージング関数を扱う
// <使い方>
//					使いたい場所で、作って、Start(元の値、初期値、最終値)をやれば動きます
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once

namespace NakashiLib
{
	class Easing {
	private:
		float change;		// 変化0～1
		float change_amount;// 実際の変化量
		bool turn;			// Turn関数用
	public:
		Easing();
		~Easing();

		//数値変更
		void Start(float speed, float strNum, float endNum);
		//終了呼び出し
		bool EndChange();
		//リセット
		void Reset();

		float GetChange() {
			return change;
		}


		//speed 1フレームの変化量,strNum 変化の初期値,endNum 変化の最終値

		float Normal(float speed, float strNum, float endNum);
		float InSine(float speed, float strNum, float endNum);
		float OutSine(float speed, float strNum, float endNum);
		float InOutSine(float speed, float strNum, float endNum);

		float InQuad(float speed, float strNum, float endNum);
		float OutQuad(float speed, float strNum, float endNum);
		float InOutQuad(float speed, float strNum, float endNum);

		float InQubic(float speed, float strNum, float endNum);
		float OutQubic(float speed, float strNum, float endNum);
		float InOutQubic(float speed, float strNum, float endNum);

		float InQuart(float speed, float strNum, float endNum);
		float OutQuart(float speed, float strNum, float endNum);
		float InOutQuart(float speed, float strNum, float endNum);

		float InQuint(float speed, float strNum, float endNum);
		float OutQuint(float speed, float strNum, float endNum);
		float InOutQuint(float speed, float strNum, float endNum);

		float InExpo(float speed, float strNum, float endNum);
		float OutExpo(float speed, float strNum, float endNum);
		float InOutExpo(float speed, float strNum, float endNum);

		float InCirc(float speed, float strNum, float endNum);
		float OutCirc(float speed, float strNum, float endNum);
		float InOutCirc(float speed, float strNum, float endNum);

		float InBack(float speed, float strNum, float endNum);
		float OutBack(float speed, float strNum, float endNum);
		float InOutBack(float speed, float strNum, float endNum);

		float InElastic(float speed, float strNum, float endNum);
		float OutElastic(float speed, float strNum, float endNum);
		float InOutElastic(float speed, float strNum, float endNum);

		float InBounce(float speed, float strNum, float endNum);
		float OutBounce(float speed, float strNum, float endNum);
		float InOutBounce(float speed, float strNum, float endNum);


		enum class EasingType
		{
			Nomal,

			InSine, OutSine, InOutSine,

			InQuad, OutQuad, InOutQuad,

			InQubic, OutQubic, InOutQubic,

			InQuart, OutQuart, InOutQuart,

			InQuint, OutQuint, InOutQuint,

			InExpo, OutExpo, InOutExpo,

			InCirc, OutCirc, InOutCirc,

			InBack, OutBack, InOutBack,

			InElastic, OutElastic, InOutElastic,

			InBounce, OutBounce, InOutBounce
		};

		//enumから選択して種類を設定する
		//Easingの種類(Easing::EasingType::〇〇),スピード,初期値,最終地
		float Selection(EasingType type, float speed, float strNum, float endNum);

		//指定された範囲を反復する
		//初期値から最終地へのタイプ,最終地から初期値へのタイプ,スピード,初期値,最終地
		float Turn(EasingType type1, EasingType type2, float speed, float strNum, float endNum);

		//指定した範囲を繰り返し続ける
		//Easingの種類(Easing::EasingType::〇〇),スピード,初期値,最終地
		float Rope(EasingType type, float speed, float strNum, float endNum);
	};

}