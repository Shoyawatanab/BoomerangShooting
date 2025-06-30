#include "UI.hlsli"

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.pos = position;

	output.tex = input.tex;
	return output;
}