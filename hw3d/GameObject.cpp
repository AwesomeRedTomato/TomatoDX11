#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Shader.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "MonoBehaviour.h"
#include "Camera.h"


void GameObject::Init()
{
	AddComponent(std::make_shared<Transform>());
}

void GameObject::Start()
{
	for (const auto& c : _components)
	{
		if (c)
			c->Start();
	}
	for (const auto& s : _scripts)
	{
		s->Start();
	}
}

void GameObject::Update()
{
	for (const auto& c : _components)
	{
		if (c)
			c->Update();
	}
	for (const auto& s : _scripts)
	{
		s->Update();
	}
}

void GameObject::LateUpdate()
{
	for (const auto& c : _components)
	{
		if (c)
			c->LateUpdate();
	}
	for (const auto& s : _scripts)
	{
		s->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (const auto& c : _components)
	{
		if (c)
			c->FinalUpdate();
	}
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	UINT index = static_cast<UINT>(component->GetType());
	_components[index] = component;

	if (index < (UINT)COMPONENT_TYPE::MONO_BEHAVIOR)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(std::dynamic_pointer_cast<MonoBehaviour>(component));
	}
}

std::shared_ptr<Transform> GameObject::GetTransform()
{
	UINT index = static_cast<UINT>(COMPONENT_TYPE::TRANSFORM);
	return std::static_pointer_cast<Transform>(_components[index]);
}

std::shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	UINT index = static_cast<UINT>(COMPONENT_TYPE::MESH_RENDERER);
	return std::static_pointer_cast<MeshRenderer>(_components[index]);
}

std::shared_ptr<Camera> GameObject::GetCamera()
{
	UINT index = static_cast<UINT>(COMPONENT_TYPE::CAMERA);
	return std::static_pointer_cast<Camera>(_components[index]);
}
