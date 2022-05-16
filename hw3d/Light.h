#pragma once
#include "Component.h"

enum class LIGHT_TYPE
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};

struct LIGHT_PARAMS
{
	FLOAT4		diffuse;
	FLOAT4		ambient;
	FLOAT4		specular;

	FLOAT4		position;
	FLOAT4		direction;

	UINT		lightType;
	float		range;
	float		angle;
	UINT		padding;
};

class Light : public Component
{
public:
	Light() : Component(COMPONENT_TYPE::LIGHT) {}
	virtual ~Light() = default;

public:
	void SetDiffuse(const FLOAT3& diffuse) { _lightParams.diffuse = diffuse; }
	void SetAmbient(const FLOAT3& ambient) { _lightParams.ambient = ambient; }
	void SetSpecular(const FLOAT3& specular) { _lightParams.specular = specular; }

	void SetLightType(LIGHT_TYPE type) { _lightParams.lightType; }


public:
	void Start();
	void Update();
	void LateUpdate();

protected:
	LIGHT_PARAMS _lightParams;
};

