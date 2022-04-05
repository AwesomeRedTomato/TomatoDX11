Texture2D texture_0 : register(t0);
SamplerState sample_0 : register(s0);

float4 main(VSOut input) : SV_Target
{
    float4 color = texture_0.Sample(sample_0, input.uv);
    return color;
}