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
  
};

cbuffer LIGHT_PARAMS : register(b3)
{
    float4 g_lightPos;
    float4 g_lightDirection;
           
    float4 g_diffuseColor;
    float4 g_ambientColor;
    float4 g_specularColor;
    
    float  g_intensity;
    int    g_lightType;
    float  g_range;
    float  g_angle;
};

Texture2D texture_0 : register(t0);
SamplerState samplerState_0 : register(s0);

#endif