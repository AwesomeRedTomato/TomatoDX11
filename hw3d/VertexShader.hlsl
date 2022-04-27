cbuffer CBuf :register(b0)
{
    matrix transform;
};

cbuffer CBuf2 : register(b1)
{
    float2 tr2;
}

//cbuffer Transform : register(b1)
//{
//    float3 position;
//    float3 rotation;
//    float3 scale;
    
//    matrix world;
//    matrix view;
//    matrix projection;
//};

struct VSOut
{
    float2 uv : TEXCOORD;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : POSITION, float2 uv : TEXCOORD)
{
    VSOut vso;
    vso.pos = mul(float4(pos, 1.f), transform);
    vso.pos += tr2.x;
    vso.uv = uv;
    return vso;
}