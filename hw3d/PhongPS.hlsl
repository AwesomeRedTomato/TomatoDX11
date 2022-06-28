#include "Params.hlsli"

float4 main(float2 uv : TEXCOORD) : SV_TARGET
{
    float4 color = texture_0.Sample(samplerState_0, uv);
    return color;
}