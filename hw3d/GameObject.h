#pragma once
#include "Component.h"
#include "Transform.h"
#include "Shader.h"
#include "Material.h"

class GameObject
{
public:
	void Init();
	void Bind();
	void Update();

	std::shared_ptr<Transform> GetTransform() { return _transform; }

public:
	std::shared_ptr<Transform> _transform;
	std::shared_ptr<Shader> _shader;

private:
	std::array<std::shared_ptr<Component>, (size_t)COMPONENT_TYPE::END> _components;

};

