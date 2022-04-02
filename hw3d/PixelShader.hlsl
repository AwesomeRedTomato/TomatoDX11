Texture2D texture_0;
SamplerState sample_0;

float4 main(float2 uv : TEXCOORD) : SV_Target
{
    return texture_0.Sample(sample_0, uv);
}