// ポイントスプライト インスタンシング用ピクセルシェーダー

// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;
    float4 CameraRight;
    float4 CameraUp;
    float4 GlobalColor;
};

// テクスチャとサンプラー
Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);

// 入力構造体（頂点シェーダーからの出力）
struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD0;
    float4 AtlasCoord : TEXCOORD1;
};

// 出力構造体
struct PS_OUTPUT
{
    float4 Color : SV_TARGET;
};

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    
    // テクスチャアトラス座標を使用してテクスチャをサンプリング
    float4 texColor = DiffuseTexture.Sample(DiffuseSampler, input.AtlasCoord.xy);
    
    // 頂点カラーとテクスチャカラーを合成
    output.Color = texColor * input.Color * GlobalColor;
    
    // アルファテスト（完全に透明なピクセルは破棄）
    if (output.Color.a < 0.01f)
    {
        discard;
    }
    
    return output;
}