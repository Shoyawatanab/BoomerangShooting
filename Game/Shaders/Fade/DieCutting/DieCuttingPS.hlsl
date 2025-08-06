#include "DieCutting.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float CalcAlpha(float2 uv, float2 center, float size)
{
    float aspect = 1280.0f / 720.0f;
	uv.x *= aspect;
	
    return step(size, distance(uv, float2(center.x * aspect, center.y)));
}



float CalcAlpha2(float2 uv, float2 center, float size)
{
    float alpha = 0;
    float aspect = 1280.0f / 720.0f;
    uv.x *= aspect; // アスペクト比の調整
	
    // centerの位置をアスペクト比に合わせて調整
    float2 adjustedCenter = center;
    adjustedCenter.x *= aspect;

    float Value = distance(uv, adjustedCenter);
	
    // 0.0fから1.0fの範囲に収めつつ、調整をする
    float x = Value / size;
	
    alpha = smoothstep(0.0f, 1.0f, x);
	
    return alpha;
}


float EraseDifference(float4 dst)
{
    return(1.0 - dst.a);
}



float4 main(PS_INPUT input) : SV_TARGET
{
	//	画像表示
	float4 output = tex.Sample(samLinear, input.Tex);

	float4 output2 = tex2.Sample(samLinear, input.Tex);


	//	真っ白なピクセル
	float4 outputw = float4(1, 1, 1, 1);
	//	真っ黒なピクセル
	float4 outputb = float4(0, 0, 0, 1);
	
    // 経過時間的な使い方をする
    float t = easing.x;
	
    output.a = CalcAlpha2(input.Tex, float2(0.5f, 0.5f), t * 50);
    
    output.a = EraseDifference(output2);
    
    return output;
}