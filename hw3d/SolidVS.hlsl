#include "Params.hlsli"

struct VSIn
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VSOut
{
    float2 uv : TEXCOORD;
    float4 pos : SV_Position;
};

VSOut main(VSIn vin)
{
    VSOut vso;
    vso.pos = mul(float4(vin.pos, 1.f), g_matWVP);
    vso.uv = vin.uv;
    return vso;
}