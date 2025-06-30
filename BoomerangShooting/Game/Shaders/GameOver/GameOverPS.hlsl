#include "GameOver.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{

    //	指定された画像の表示
    float4 output = tex.Sample(samLinear, input.Tex);
        
    //経過時間
    float time = Time.x;
    
    //最大時間
    float maxTime = Time.y;
    //進行割合
    float ratio = time / maxTime;
    
    output.a = lerp(0.0f, 1.0f, ratio);
	
    return output;
}