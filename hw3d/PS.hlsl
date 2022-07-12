#include "Params.hlsli"
#include "Utils.hlsli"

struct VSOut
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
    float3 viewPos : POSITION;
    float3 viewNormal : NORMAL;
};

float4 main(VSOut pin) : SV_TARGET
{
    float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    LightColor totalColor = (LightColor)0.0f;
    
    for (int i = 0; i < g_lightCount; ++i)
    {
        LightColor color = CalculateLightColor(i, pin.viewNormal, pin.viewPos);
        totalColor.ambient += color.ambient;
        totalColor.diffuse += color.diffuse;
        totalColor.specular += color.specular;
    }
    
    color.xyz = (totalColor.diffuse.xyz * color.xyz) +
             (totalColor.ambient.xyz * color.xyz) +
             (totalColor.specular.xyz * color.xyz);
    
    return color;
}