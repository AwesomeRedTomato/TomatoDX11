#pragma once
#include "Component.h"
class MonoBehaviour : public Component
{
public:
	MonoBehaviour() : Component(COMPONENT_TYPE::MONO_BEHAVIOR) {}
	virtual ~MonoBehaviour() {};

public:

private:
};

