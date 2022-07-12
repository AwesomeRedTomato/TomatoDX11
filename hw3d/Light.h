#pragma once
#include "Component.h"

enum class LIGHT_TYPE
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};

struct LightColor
{
	FLOAT4		ambient;
	FLOAT4		diffuse;
	FLOAT4		specular;
};

struct LightInfo
{
	LightColor  color;

	FLOAT4		position;
	FLOAT4		direction;
	UINT		type;

	float		range;	// point light radius
	float		angle;
	UINT		padding;
};

struct LIGHT_PARAMS
{
	UINT		lightCount;
	FLOAT3		padding;
	LightInfo	lights[50];
};

class Light : public Component
{
public:
	Light();
	virtual ~Light() = default;

public:
	virtual void FinalUpdate() override;
	virtual	void UpdateImGui() override;

public:
	const LightInfo& GetLightInfo() { return _lightInfo; }

	void SetLightType(LIGHT_TYPE type) { _lightInfo.type = static_cast<UINT>(type); }

public:
	LightInfo _lightInfo = {};
};