#include "pch.h"
#include "SceneManager.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Material.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "Cube.h"
#include "Sphere.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"

void SceneManager::LoadScene()
{
	_activeScene = LoadTestScene();
	_activeScene->Start();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FinalUpdate();
}

void SceneManager::UpdateImgui()
{
	_activeScene->UpdateImGui();
	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void SceneManager::Render()
{
	if (_activeScene)
		_activeScene->Render();

}

std::shared_ptr<Scene> SceneManager::LoadTestScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

#pragma region Cube
	{
		std::shared_ptr<GameObject> objCube = std::make_shared<GameObject>();
		objCube->SetObjectName("Cube");
		objCube->AddComponent(std::make_shared<Transform>());

		std::shared_ptr<Transform> transform = objCube->GetTransform();
		transform->SetLocalPosition(FLOAT3(0.0f, 0.0f, 0.7f));
		transform->SetLocalScale(FLOAT3(1.0f, 1.0f, 1.0f));
		transform->SetLocalRotation(FLOAT3(70.0f, 70.0f, 0.0f));

		auto meshRenderer = std::make_shared<MeshRenderer>();
		{
			auto mesh = std::make_shared<Mesh>();
			auto cube = std::make_shared<Cube>();
			mesh->Init(cube->vertices, cube->indices);

			auto shader = std::make_shared<Shader>();
			shader->Init();

			auto texture = std::make_shared<Texture>();
			texture->Load(L"Image\\Leather.jpg");
			texture->Init();

			auto material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(TEXTURE_TYPE::DIFFUSE, texture);

			meshRenderer->SetMesh(mesh);
			meshRenderer->SetMaterial(material);
		}
		objCube->AddComponent(meshRenderer);
		scene->AddGameObject(objCube);
	}
#pragma endregion


#pragma region Camera
	{
		std::shared_ptr<GameObject> camera = std::make_shared<GameObject>();
		camera->SetObjectName("Camera");
		camera->AddComponent(std::make_shared<Transform>());
		camera->AddComponent(std::make_shared<Camera>()); // Near=1, Far=1000, FOV=45µµ
		camera->GetTransform()->SetLocalPosition(FLOAT3(0.0f, 0.0f, -10.0f));
		scene->AddGameObject(camera);
	}
#pragma endregion

#pragma region Light
	{
		std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
		light->SetObjectName("Light");

		auto meshRenderer = std::make_shared<MeshRenderer>();
		{
			auto mesh = std::make_shared<Mesh>();
			auto cube = std::make_shared<Cube>();
			mesh->Init(cube->vertices, cube->indices);

			auto shader = std::make_shared<Shader>();
			shader->Init();

			auto texture = std::make_shared<Texture>();
			texture->Load(L"Image\\Leather.jpg");
			texture->Init();

			auto material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(TEXTURE_TYPE::DIFFUSE, texture);

			meshRenderer->SetMesh(mesh);
			meshRenderer->SetMaterial(material);
		}
		light->AddComponent(meshRenderer);
		light->AddComponent(std::make_shared<Transform>());
		light->AddComponent(std::make_shared<Light>());
		light->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
		light->GetTransform()->SetLocalScale(FLOAT3(0.1f, 0.1f, 0.1f));
		light->GetTransform()->SetLocalPosition(FLOAT3(1.0f, -0.6f, -6.0f));
		scene->AddGameObject(light);

	}
#pragma endregion


	return scene;
}