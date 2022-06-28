#pragma once
#include "Component.h"

enum class LIGHT_TYPE
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};

class Light : public Component
{
public:
	Light();
	virtual ~Light() = default;

public:
	virtual void FinalUpdate() override;
	virtual	void UpdateImGui() override;
	void PushData();

public:
	void SetType(LIGHT_TYPE type) { _lightParams.lightType = (UINT)type; }

public:
	LIGHT_PARAMS _lightParams = {};
};