#include "Fade.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	真っ黒な板ポリゴン
    float4 outputb = float4(0, 0, 0, 1);

    //経過時間
    float time = Time.x;
    
    //最大時間
    float maxTime = Time.y;
    //進行割合
    float ratio = time / maxTime;
    
    outputb.a = lerp(1.0f,0.0f,ratio);
	
    return outputb;
}