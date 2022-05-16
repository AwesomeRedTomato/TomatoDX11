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
}

void SceneManager::UpdateImgui()
{
	static int counter = 0;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static float a = 0.0f;

	ImGui::Begin("Transform");

	ImGui::SliderFloat("R", &a, 50.0f, 80.0f, "%.1f");

	std::string clickCount = "Click Count: " + std::to_string(counter);
	ImGui::Text(clickCount.c_str());
	ImGui::End();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

std::shared_ptr<Scene> SceneManager::LoadTestScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	gameObject->Init();

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
	//auto camera = std::make_shared<Camera>();
	//gameObject->AddComponent(camera);

	gameObject->AddComponent(meshRenderer);
	
	scene->AddGameObject(gameObject);

	return scene;

}
