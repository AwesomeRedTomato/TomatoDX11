#include "pch.h"
#include "SceneManager.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Material.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "Cube.h"
#include "Transform.h"
#include "Camera.h"

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
	if (_activeScene == nullptr)
		return;

	const std::vector<std::shared_ptr<GameObject>>& gameObjects = _activeScene->GetGameObject();
	
	for (const auto& g : gameObjects)
	{
		if (g->GetCamera() == nullptr)
			continue;

		g->GetCamera()->Render();
	}
}

std::shared_ptr<Scene> SceneManager::LoadTestScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

#pragma region Cube
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	gameObject->SetObjectName("Cube");
	gameObject->AddComponent(std::make_shared<Transform>());

	std::shared_ptr<Transform> transform = gameObject->GetTransform();
	transform->SetLocalPosition(FLOAT3(0.0f, 100.0f, 0.0f));
	transform->SetLocalScale(FLOAT3(100.0f, 100.0f, 100.0f));

	auto meshRenderer = std::make_shared<MeshRenderer>();
	{
		auto mesh = std::make_shared<Mesh>();
		auto cube = std::make_shared<Cube>();
		mesh = cube->Init();
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
	gameObject->AddComponent(meshRenderer);
#pragma endregion
	scene->AddGameObject(gameObject);


#pragma region Camera
	std::shared_ptr<GameObject> camera = std::make_shared<GameObject>();
	camera->SetObjectName("Camera");
	camera->AddComponent(std::make_shared<Transform>());
	camera->AddComponent(std::make_shared<Camera>()); // Near=1, Far=1000, FOV=45µµ
	camera->GetTransform()->SetLocalPosition(FLOAT3(0.f, 100.f, 0.f));
	scene->AddGameObject(camera);
#pragma endregion


	return scene;
}
