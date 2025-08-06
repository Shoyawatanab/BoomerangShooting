#include "UI.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	Žw’è‚³‚ê‚½‰æ‘œ‚Ì•\Ž¦
    float4 output = tex.Sample(samLinear, input.tex);

    float visible = step(input.tex.x, FillAmount.x);
    
    output *= visible;
    output *= color;
    
    return output;
    
}