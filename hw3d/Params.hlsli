#ifndef _PARAMS_HLSLI_
#define _PARAMS_HLSLI_

cbuffer TRANSFORM_PARAMS : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProjection;
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
};

cbuffer MATERIAL_PARAMS : register(b1)
{
    int g_tex_on_0;
    int g_tex_on_1;
};

cbuffer COLOR_PARAMS : register(b2)
{
    float g_color;
};

struct LightColor
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
};

struct LightInfo
{
    LightColor  color;
    
    float4      position;
    float4      direction;
    int         type;          // directional, spot, point
           
    float       range;         // light range
    float       angle;         // direction
    int       padding;
};

cbuffer LIGHT_PARAMS : register(b3)
{
    int         g_lightCount;
    float3      padding;
    LightInfo   g_light[50];
};

Texture2D texture_0 : register(t0);
SamplerState samplerState_0 : register(s0);

#endif