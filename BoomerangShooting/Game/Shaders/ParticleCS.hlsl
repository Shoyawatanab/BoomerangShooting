// コンスタントバッファ
cbuffer ConstBuffer : register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProj;
};

// 出力先のRWTexture
RWTexture2D<float4> OutputTexture : register(u0);

// スレッドグループサイズ（16x16）
[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint width, height;
    OutputTexture.GetDimensions(width, height);

    float2 uv = float2(DTid.xy) / float2(width, height);

    // 色をUVベースのグラデーションで出力
    float4 color = float4(uv.x, uv.y, 1.0 - uv.x, 1.0); // R=U, G=V, B=反転

    OutputTexture[DTid.xy] = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    
}