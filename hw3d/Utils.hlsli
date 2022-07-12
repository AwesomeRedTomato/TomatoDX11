#include "Params.hlsli"

#ifndef _UTILS_HLSLI_
#define _UTILS_HLSLI_

LightColor CalculateLightColor(int lightIndex, float3 viewNormal, float3 viewPos)
{
    LightColor color = (LightColor) 0.0f;
    
    float3 viewLightDir = (float3) 0.0f;
    
    float diffuseRatio = 0.0f;
    float specularRatio = 0.0f;
    float distanceRatio = 1.0f;
    
    // Directional Light
    if(g_light[lightIndex].type == 0)
    {
        viewLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.0f), g_matView).xyz);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
    }
    // Point Light
    else if(g_light[lightIndex].type == 1)
    {
        float3 viewLightPos = mul(float4(g_light[lightIndex].pos.xyz, 1.0f), g_matView).xyz;
        viewLightDir = normalize(viewPos - viewLightDir);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
        
        float dist = distance(viewPos, viewLightPos);
        if (g_light[lightIndex].range == 0.0f)
            distanceRatio = 0.0f;
        else
            distanceRatio = saturate(1.0f - pow(dist / g_light[lightIndex].range, 2));
    }
    //// Spot Light
    //else
    //{
    //    float3 viewLightPos = mul(float4(g_light[lightIndex].pos.xyz, 1.0f), g_matView));
    //    viewLightDir = 
    //}
    
    float3 reflectionDir = normalize(viewLightDir + 2 * (saturate(dot(-viewLightDir, viewNormal)) * viewNormal));
    float3 eyeDir = normalize(viewPos);
    
    specularRatio = pow(saturate(dot(-eyeDir, reflectionDir)), 2);

    color.diffuse = g_light[lightIndex].color.diffuse * diffuseRatio * distanceRatio;
    color.ambient = g_light[lightIndex].color.ambient * distanceRatio;
    color.specular = g_light[lightIndex].color.specular * specularRatio * distanceRatio;
    
    return color;
}

#endif