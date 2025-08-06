
#ifndef EASING_FUNCTIONS_H
#define EASING_FUNCTIONS_H

// インクルード
#include "pch.h"
#include <cmath>

// M_PI が定義されていない場合は手動で定義
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/// <summary>
/// イージング関数
/// </summary>
class Easing
{
public:
	/// <summary>
	/// イーズインサイン関数
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInSine(float easing) {
		return 1.0f - static_cast<float>(cos((easing * M_PI) / 2.0f));
	}

	/// <summary>
	/// イーズアウトサイン関数
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeOutSine(float easing) {
		return static_cast<float>(sin((easing * M_PI) / 2.0f));
	}

	/// <summary>
	/// イーズインアウトサイン関数
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutSine(float easing) {
		return static_cast<float>(-(cos(M_PI * easing) - 1.0) / 2.0);
	}

	/// <summary>
	/// イーズイン二次関数（加速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInQuad(float easing) {
		return easing * easing;
	}

	/// <summary>
	/// イーズインアウト二次関数（加速・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutQuad(float easing) {
		return easing < 0.5f ? 2.0f * easing * easing : 1.0f - static_cast<float>(pow(-2.0f * easing + 2.0f, 2) / 2.0);
	}

	/// <summary>
	/// イーズインキュービック関数（三次関数・加速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInCubic(float easing) {
		return easing * easing * easing;
	}

	/// <summary>
	/// イーズアウトキュービック関数（三次関数・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeOutCubic(float easing) {
		return 1.0f - static_cast<float>(pow(1.0f - easing, 3));
	}

	/// <summary>
	/// イーズインアウトキュービック関数（三次関数・加速・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutCubic(float easing) {
		return easing < 0.5f ? 4.0f * easing * easing * easing : 1.0f - static_cast<float>(pow(-2.0f * easing + 2.0f, 3) / 2.0);
	}

	/// <summary>
	/// イーズインクォート関数（四次関数・加速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInQuart(float easing) {
		return easing * easing * easing * easing;
	}

	/// <summary>
	/// イーズアウトクォート関数（四次関数・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeOutQuart(float easing) {
		return 1.0f - static_cast<float>(pow(1.0f - easing, 4));
	}

	/// <summary>
	/// イーズインアウトクォート関数（四次関数・加速・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutQuart(float easing) {
		return easing < 0.5f ? 8.0f * easing * easing * easing * easing : 1.0f - static_cast<float>(pow(-2.0f * easing + 2.0f, 4) / 2.0);
	}

	/// <summary>
	/// イーズインクィント関数（五次関数・加速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInQuint(float easing) {
		return easing * easing * easing * easing * easing;
	}

	/// <summary>
	/// イーズアウトクィント関数（五次関数・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeOutQuint(float easing) {
		return 1.0f - static_cast<float>(pow(1.0f - easing, 5));
	}

	/// <summary>
	/// イーズインアウトクィント関数（五次関数・加速・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutQuint(float easing) {
		return easing < 0.5f ? 16.0f * easing * easing * easing * easing * easing : 1.0f - static_cast<float>(pow(-2.0f * easing + 2.0f, 5) / 2.0);
	}

	/// <summary>
	/// イーズインエクスポ関数（指数関数・加速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInExpo(float easing) {
		return easing == 0 ? 0 : static_cast<float>(pow(2.0, 10.0f * easing - 10.0f));
	}

	/// <summary>
	/// イーズアウトエクスポ関数（指数関数・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeOutExpo(float easing) {
		return easing == 1 ? 1 : 1.0f - static_cast<float>(pow(2.0, -10.0f * easing));
	}

	/// <summary>
	/// イーズインアウトエクスポ関数（指数関数・加速・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutExpo(float easing) {
		return easing == 0 ?
			0 : easing == 1 ?
			1 : easing < 0.5f ?
			static_cast<float>(pow(2.0, 20.0f * easing - 10.0f) / 2.0) :
			static_cast<float>((2.0f - pow(2.0, -20.0f * easing + 10.0f)) / 2.0);
	}

	/// <summary>
	/// イーズインサーク関数（円弧関数・加速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInCirc(float easing) {
		return 1.0f - static_cast<float>(sqrt(1.0f - pow(easing, 2)));
	}

	/// <summary>
	/// イーズアウトサーク関数（円弧関数・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeOutCirc(float easing) {
		return static_cast<float>(sqrt(1.0f - pow(easing - 1.0f, 2)));
	}

	/// <summary>
	/// イーズインアウトサーク関数（円弧関数・加速・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutCirc(float easing) {
		return easing < 0.5f ? static_cast<float>((1.0f - sqrt(1.0f - pow(2.0f * easing, 2))) / 2.0) : static_cast<float>((sqrt(1.0f - pow(-2.0f * easing + 2.0f, 2)) + 1.0f) / 2.0);
	}

	/// <summary>
	/// イーズインバック関数（オーバーシュート・加速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInBack(float easing) {
		const float overshoot = 1.70158f;
		const float factor = overshoot + 1.0f;
		return factor * easing * easing * easing - overshoot * easing * easing;
	}

	/// <summary>
	/// イーズアウトバック関数（オーバーシュート・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeOutBack(float easing) {
		const float overshoot = 1.70158f;
		const float factor = overshoot + 1.0f;
		return 1.0f + factor * static_cast<float>(pow(easing - 1.0f, 3)) + overshoot * static_cast<float>(pow(easing - 1.0f, 2));
	}

	/// <summary>
	/// イーズインアウトバック関数（オーバーシュート・加速・減速）
	/// </summary>
	/// <param name="easing">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutBack(float easing) {
		const float overshoot = 1.70158f;
		const float adjustedOvershoot = overshoot * 1.525f;
		return easing < 0.5f
			? static_cast<float>((pow(2.0f * easing, 2) * ((adjustedOvershoot + 1.0f) * 2.0f * easing - adjustedOvershoot)) / 2.0)
			: static_cast<float>((pow(2.0f * easing - 2.0f, 2) * ((adjustedOvershoot + 1.0f) * (2.0f * easing - 2.0f) + adjustedOvershoot) + 2.0f) / 2.0);
	}

	/// <summary>
	/// イーズイン・エラスティック関数（弾むような加速）
	/// </summary>
	/// <param name="progress">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInElastic(float progress) {
		const float period = (2.0f * M_PI) / 3.0f;
		return progress == 0 ? 0 : progress == 1 ? 1 : -static_cast<float>(pow(2.0, 10.0f * progress - 10.0f) * sin((progress * 10.0f - 10.75f) * period));
	}

	/// <summary>
	/// イーズアウト・エラスティック関数（弾むような減速）
	/// </summary>
	/// <param name="progress">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeOutElastic(float progress) {
		const float period = (2.0f * M_PI) / 3.0f;
		return progress == 0 ? 0 : progress == 1 ? 1 : static_cast<float>(pow(2.0, -10.0f * progress) * sin((progress * 10.0f - 0.75f) * period) + 1.0f);
	}

	/// <summary>
	/// イーズインアウト・エラスティック関数（弾むような加速・減速）
	/// </summary>
	/// <param name="progress">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutElastic(float progress) {
		const float period = (2.0f * M_PI) / 4.5f;
		return progress == 0 ?
			0 : progress == 1 ?
			1 : progress < 0.5f ?
			static_cast<float>(-(pow(2.0, 20.0f * progress - 10.0f) * sin((20.0f * progress - 11.125f) * period)) / 2.0) :
			static_cast<float>((pow(2.0, -20.0f * progress + 10.0f) * sin((20.0f * progress - 11.125f) * period)) / 2.0 + 1.0f);
	}

	/// <summary>
	/// イーズイン・バウンス関数（跳ねるような加速）
	/// </summary>
	/// <param name="progress">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInBounce(float progress) {
		return 1.0f - easeOutBounce(1.0f - progress);
	}

	/// <summary>
	/// イーズアウト・バウンス関数（跳ねるような減速）
	/// </summary>
	/// <param name="progress">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeOutBounce(float progress) {
		const float coefficient = 7.5625f;
		const float divisor = 2.75f;
		if (progress < 1.0f / divisor) {
			return coefficient * progress * progress;
		}
		else if (progress < 2.0f / divisor) {
			return coefficient * (progress -= 1.5f / divisor) * progress + 0.75f;
		}
		else if (progress < 2.5f / divisor) {
			return coefficient * (progress -= 2.25f / divisor) * progress + 0.9375f;
		}
		else {
			return coefficient * (progress -= 2.625f / divisor) * progress + 0.984375f;
		}
	}

	/// <summary>
	/// イーズインアウト・バウンス関数（跳ねるような加速・減速）
	/// </summary>
	/// <param name="progress">補間の進行度（0.0～1.0）</param>
	/// <returns>補間後の値</returns>
	static float easeInOutBounce(float progress) {
		return progress < 0.5
			? (1 - easeOutBounce(1 - 2 * progress)) / 2
			: (1 + easeOutBounce(2 * progress - 1)) / 2;
	}

	/// <summary>
	/// イーズイン・イーズアウトの中間点を設定する補間関数（前半はOut、後半はIn）
	/// </summary>
	/// <param name="t">補間の進行度（0.0～1.0）</param>
	/// <param name="threshold">前半と後半の切り替えポイント（0.0～1.0）</param>
	/// <param name="firstSize">補間開始時の値</param>
	/// <param name="maxSize">補間終了時の値</param>
	/// <returns>補間後の値</returns>
	static float easeBetweenIn(float t, float threshold, float firstSize, float maxSize)
	{
		// threshold が 0 ~ 1 の範囲外の場合、補正
		threshold = std::clamp(threshold, 0.0f, 1.0f);

		if (t <= threshold) {
			return firstSize * Easing::easeOutBack(t / threshold);
		}
		else {
			return firstSize + (maxSize - firstSize) * Easing::easeInQuad((t - threshold) / (1.0f - threshold));
		}
	}

	/// <summary>
	/// イーズアウト・イーズインの中間点を設定する補間関数（前半はOut、後半はInOut）
	/// </summary>
	/// <param name="t">補間の進行度（0.0～1.0）</param>
	/// <param name="threshold">前半と後半の切り替えポイント（0.0～1.0）</param>
	/// <param name="firstSize">補間開始時の値</param>
	/// <param name="maxSize">補間終了時の値</param>
	/// <returns>補間後の値</returns>
	static float easeBetweenOut(float t, float threshold, float firstSize, float maxSize)
	{
		// threshold が 0 ~ 1 の範囲外の場合、補正
		threshold = std::clamp(threshold, 0.0f, 1.0f);

		if (t <= threshold)
		{
			return firstSize * Easing::easeOutSine(t / threshold);
		}
		else
		{
			return firstSize + (maxSize - firstSize) * Easing::easeInOutCubic((t - threshold) / (1.0f - threshold));
		}
	}
};

#endif // EASING_FUNCTIONS_H