// ポイントスプライト インスタンシング用頂点シェーダー

// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;
    float4 CameraRight;
    float4 CameraUp;
    float4 GlobalColor;
    bool onBillboard;
    float3 dammy;
};

// 入力構造体
struct VS_INPUT
{
    // ベース頂点データ
    float3 Position : POSITION;
    float2 TexCoord : TEXCOORD;
    
    // インスタンスデータ
    float3 InstancePos : INSTANCEPOS;
    float3 InstanceSize : INSTANCESIZE;
    float4 InstanceColor : INSTANCECOLOR;
    float4 InstanceTexCoord : INSTANCETEXCOORD;
    float4 InstanceRotation : INSTANCEROT;
};

// 出力構造体
struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD0;
    float4 AtlasCoord : TEXCOORD1;
};

float3x3 QuaternionToMatrix(float4 q)
{
    float x2 = q.x + q.x;
    float y2 = q.y + q.y;
    float z2 = q.z + q.z;

    float xx2 = q.x * x2;
    float yy2 = q.y * y2;
    float zz2 = q.z * z2;
    float xy2 = q.x * y2;
    float xz2 = q.x * z2;
    float yz2 = q.y * z2;
    float wx2 = q.w * x2;
    float wy2 = q.w * y2;
    float wz2 = q.w * z2;

    float3x3 m;
    m[0] = float3(1.0f - (yy2 + zz2), xy2 + wz2, xz2 - wy2);
    m[1] = float3(xy2 - wz2, 1.0f - (xx2 + zz2), yz2 + wx2);
    m[2] = float3(xz2 + wy2, yz2 - wx2, 1.0f - (xx2 + yy2));
    return m;
}

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    float3 scaled = input.Position * input.InstanceSize;
    float3x3 rotMat = QuaternionToMatrix(input.InstanceRotation);
    float3 rotated = mul(rotMat, scaled);

    float3 worldPos;

    if (onBillboard)
    {
        float3 right = normalize(CameraRight.xyz);
        float3 up = normalize(CameraUp.xyz);

        worldPos = input.InstancePos + right * rotated.x + up * rotated.y;
    }
    else
    {
        worldPos = mul(rotMat, scaled) + input.InstancePos;
    }

    float4 viewPos = mul(float4(worldPos, 1.0f), View);
    output.Position = mul(viewPos, Projection);

    output.Color = input.InstanceColor;
    output.TexCoord = input.TexCoord;

    float2 atlasOffset = input.InstanceTexCoord.xy;
    float2 atlasSize = input.InstanceTexCoord.zw;
    output.AtlasCoord.xy = atlasOffset + input.TexCoord * atlasSize;
    output.AtlasCoord.zw = float2(0.0f, 0.0f);

    return output;
}