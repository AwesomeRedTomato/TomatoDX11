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
    int tex_on_0;
    int tex_on_1;
};

cbuffer LIGHT_PARAMS : register(b3)
{
    float4 diffuse;
    float4 ambient;
    float4 specular;
    
    float4 position;
    float4 direction;
    
    int lightType;
    
    float range;
    float angle;
    int padding;
};

Texture2D texture_0 : register(t0);
SamplerState samplerState_0 : register(s0);

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
