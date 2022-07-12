#include "pch.h"	
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "Graphics.h"

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

void Scene::Render()
{
	PushLightData();

	for (auto& g : _gameObjects)
	{
		if (g->GetCamera() == nullptr)
			continue;

		g->GetCamera()->Render();
	}
}

void Scene::PushLightData()
{
	LIGHT_PARAMS lightParams = {};
	
	for (auto& g : _gameObjects)
	{
		if (g->GetLight() == nullptr)
			continue;

		const LightInfo& lightInfo = g->GetLight()->GetLightInfo();

		lightParams.lights[lightParams.lightCount] = lightInfo;
		++lightParams.lightCount;
	}
	CONSTANT_BUFFER(CB_TYPE::LIGHT)->Init(static_cast<UINT>(CB_TYPE::LIGHT), sizeof(LIGHT_PARAMS), lightParams.lightCount);
	CONSTANT_BUFFER(CB_TYPE::LIGHT)->PushPixelConstant(&lightParams); // 수정 예정
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
