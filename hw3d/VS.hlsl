#include "Params.hlsli"
#include "Utils.hlsli"
struct VSIn
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
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
    VSOut vso = (VSOut)0;
    
    vso.pos = mul(float4(vin.pos, 1.0f), g_matWVP);
    vso.uv = vin.uv;
    vso.viewPos = mul(float4(vin.pos, 1.0f), g_matWV).xyz;
    vso.viewNormal = normalize(mul(float4(vin.normal, 0.0f), g_matWV).xyz);
    
    return vso;
}