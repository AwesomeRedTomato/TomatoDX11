cbuffer TRANSFORM_PARAMS : register(b0)
{
    matrix matView;
    matrix matViewProjection;
};

cbuffer MATERIAL_PARAMS : register(b1)
{
    int tex_on_0;
    int tex_on_1;
};

cbuffer TR : register(b2)
{
    matrix transform;
}

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