#include "UI.hlsli"

static const float2 center = float2(-1, 1);

static const unsigned int vnum = 4;

//wが0だと行列計算がおかしくなるので1に変更
static const float4 offset_array[vnum] =
{
	float4( -0.5f,  0.5f, 0.0f, 1.0f),	// 左上
	float4( 0.5f,  0.5f, 0.0f, 1.0f),	// 右上
	float4( -0.5f,  -0.5f, 0.0f, 1.0f),	// 左下
	float4( 0.5f,  -0.5f, 0.0f, 1.0f),	// 右下

};


static const float2 offset_UV[vnum] =
{
    float2(0.0f, 0.0f), //	左上
	float2(1.0f, 0.0f), //	右上
	float2(0.0f, 1.0f), //	左下
	float2(1.0f, 1.0f), //	右下

};

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream< PS_INPUT > output
)
{
    
    float cosA = cos(rotate.x);
    float sinA = sin(rotate.x);

    for (uint i = 0; i < vnum; i++)
    {
        PS_INPUT element;

        float2 window = windowSize.xy;

    // スクリーン座標化されたポジション
        float2 Position = input[0].pos.xy / window * 2.0f;
        Position = float2(center.x + Position.x, center.y - Position.y);

    // ローカル座標を定義 [-0.5, 0.5] → スケーリング（画像サイズ）
        float2 local = offset_array[i].xy * size.xy;

    // 回転
        float2 rotated;
        rotated.x = local.x * cosA - local.y * sinA;
        rotated.y = local.x * sinA + local.y * cosA;

    // ビュー拡大縮小
        rotated *= viewRange.xy;

    // 最終座標をスクリーン基準に変換
        float2 final = rotated / window * 2.0f;
        element.pos.xy = Position + final;
        element.pos.z = 0.0f;
        element.pos.w = 1.0f;

    // UVはそのままでOK
        element.tex = float2(
        clipRange.x + clipRange.z * offset_UV[i].x,
        clipRange.y + clipRange.w * offset_UV[i].y
    );

        output.Append(element);
    }

    output.RestartStrip();
	
}