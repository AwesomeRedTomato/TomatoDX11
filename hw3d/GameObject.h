#pragma once
#include "Component.h"
#include "Transform.h"
#include "Shader.h"
#include "Material.h"
#include "MonoBehaviour.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	void Init();

	void Start();
	void Update();
	void LateUpdate();

public:
	void AddComponent(std::shared_ptr<Component> component);

public:
	std::shared_ptr<Transform> GetTransform();

private:
	std::array<std::shared_ptr<Component>, (size_t)COMPONENT_TYPE::END> _components;
	std::vector<std::shared_ptr<MonoBehaviour>> _scripts;
};

