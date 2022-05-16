#pragma once
#include "MonoBehaviour.h"
class TestCamera : public MonoBehaviour
{
public:
	TestCamera() = default;
	virtual ~TestCamera() = default;

public:
	virtual void LateUpdate() override;

private:
	float _speed = 100.0f;
};

