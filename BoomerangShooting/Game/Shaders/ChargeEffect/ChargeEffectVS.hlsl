#include "ChargeEffect.hlsli"

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

    output.Pos = mul(float4(input.Pos, 1), matWorld);
    output.Pos = mul(output.Pos, matView);
    output.Pos = mul(output.Pos, matProj);
    
	//UV座標はそのまま渡す
    output.Tex = input.Tex;
	//次のシェーダへ情報を渡す
	return output;
    
}