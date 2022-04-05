#pragma once
#include "Component.h"

class Transform;

class GameObject
{
public:
	void Init();
	void Bind();
	void Update();

	std::shared_ptr<Transform> GetTransform() { return _transform; }

public:
	std::shared_ptr<Transform> _transform;

private:

};

