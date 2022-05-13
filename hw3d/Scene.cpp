#include "pch.h"	
#include "Scene.h"
#include "GameObject.h"

void Scene::Start()
{
	for (auto& g : _gameObjects)
	{
		g->Start();
	}
}

void Scene::Update()
{
	for (auto& g : _gameObjects)
	{
		g->Update();
	}
}

void Scene::LateUpdate()
{
	for (auto& g : _gameObjects)
	{
		g->LateUpdate();
	}

}

void Scene::Render()
{
	for (auto& g : _gameObjects)
	{
		g->GetCamera()->Render();
	}
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject)
{
	auto iter = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);

	if (iter != _gameObjects.end())
	{
		_gameObjects.erase(iter);
	}
}
