cbuffer CBuf
{
    matrix transform;
};

struct VSOut
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

VSOut main(float3 pos : POSITION, float2 uv : TEXCOORD)
{
    VSOut vso;
    vso.pos = mul(float4(pos, 1.f), transform);
    vso.uv = uv;
    return vso;
}