#include "Params.hlsli"

struct VSIn
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VSOut
{
    float3 viewNormal : NORMAL;
    float3 viewPos : POSITION;
    float2 uv : TEXCOORD;
    float4 pos : SV_Position;
};

VSOut main(VSIn vin)
{
    VSOut vso;
    
    vso.pos = mul(float4(vin.pos, 1.0f), g_matWVP);
    vso.uv = vin.uv;
    vso.viewPos = mul(float4(vin.pos, 1.0f), g_matWV);
    vso.viewNormal = normalize(mul(float4(vin.normal, 1.0f), g_matWV));
    
    return vso;
}