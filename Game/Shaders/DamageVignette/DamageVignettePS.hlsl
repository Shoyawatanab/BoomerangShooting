#include "DamageVignette.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);



float4 main(PS_INPUT input) : SV_TARGET
{
   
    float2 uv = input.Tex;
    uv -= 0.5f; // UV座標を中心に移動（[-0.5, 0.5] に変換）

    // 中央からの距離を計算
    float dist = length(uv);

// 外枠の幅（赤色から透明への遷移範囲の開始と終了）
    float vignetteStart = 1.5f; // 赤色が始まる位置（外枠）
    float vignetteEnd = 1.33f; // 赤色が完全に透明になる位置

    // アルファ値の計算（透明度を制御）
    float alpha = smoothstep(vignetteEnd, vignetteStart, dist);

    // 赤色の生成（アルファを反映）
    float4 baseColor = float4(1, 0, 0, alpha);

    // 内側は透明
    float innerAlpha = smoothstep(0.0f, vignetteEnd, dist);
    float4 innerColor = float4(1, 0, 0, innerAlpha * time.x);

    // 結果を合成（外枠を赤、内側を透明）
    return lerp(innerColor, baseColor,  alpha );

}