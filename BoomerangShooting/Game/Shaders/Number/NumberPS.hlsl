#include "Number.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{

    float2 uv = input.tex;
    
    int number = diffuse.x;

    float width = 10.0f;
    
    uv.x /= width;

   uv.x += (1.0f / width) * number;
    
    float4 output = tex.Sample(samLinear,uv);    
    
    
    
    return output;
    
}