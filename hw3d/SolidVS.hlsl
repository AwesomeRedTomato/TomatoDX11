#include "Params.hlsli"

VSOut main(VSIn vin)
{
    VSOut vso;
    vso.pos = mul(float4(vin.pos, 1.f), g_matWVP);
    vso.uv = vin.uv;
    return vso;
}