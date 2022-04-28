#include "pch.h"
#include "Component.h"
#include "GameObject.h"

std::shared_ptr<GameObject> Component::GetGameObject()
{
	return _gameObject.lock();
}

std::shared_ptr<Transform> Component::GetTransform()
{
	return _gameObject.lock()->GetTransform();
}
