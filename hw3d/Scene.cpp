#include "pch.h"	
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"

void Scene::Start()
{
	for (const auto& g : _gameObjects)
	{
		g->Start();
	}
}

void Scene::Update()
{
	for (const auto& g : _gameObjects)
	{
		g->Update();
	}
}

void Scene::LateUpdate()
{
	for (const auto& g : _gameObjects)
	{
		g->LateUpdate();
	}

}

void Scene::FinalUpdate()
{
	for (const auto& g : _gameObjects)
	{
		g->FinalUpdate();
	}
}

void Scene::UpdateImGui()
{
	for (const auto& g : _gameObjects)
	{
		g->UpdateImGui();
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
