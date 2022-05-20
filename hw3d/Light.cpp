#include "pch.h"
#include "Light.h"
#include "Transform.h"

void Light::FinalUpdate()
{
	_lightParams.position = GetTransform()->GetWorldPosition();
}
