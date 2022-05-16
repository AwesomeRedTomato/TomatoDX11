cbuffer TRANSFORM_PARAMS :register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProjection;
    matrix matWV;
    matrix matWVP;
};

cbuffer MATERIAL_PARAMS : register(b1)
{
    int tex_on_0;
    int tex_on_1;
};

// 수정 예정
cbuffer TR : register(b2)
{
    matrix transform;
}

Texture2D tex2D_0 : register(t0);
Texture2D tex2D_1 : register(t1);

struct VSOut
{
    float2 uv : TEXCOORD;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : POSITION, float2 uv : TEXCOORD)
{
    VSOut vso;
    vso.pos = mul(float4(pos, 1.f), transform);
    vso.uv = uv;
    return vso;
}