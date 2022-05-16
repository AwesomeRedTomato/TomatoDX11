#include "pch.h"
#include "Camera.h"
#include "Graphics.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"
#include "MeshRenderer.h"

MATRIX Camera::S_MatView;
MATRIX Camera::S_MatProjection;


void Camera::FinalUpdate()
{
	_matView = GetTransform()->GetWorldMatrix();

	_matProjection = XMMatrixPerspectiveFovLH(_fov, _gfx->GetAspectRatio(), _near, _far);

	S_MatView = _matView;
	S_MatProjection = _matProjection;
}

void Camera::Render()
{
	std::shared_ptr<Scene> scene = GET_SINGLE(SceneManager)->GetActiveScene();

	const std::vector<std::shared_ptr<GameObject>>& gameObjects = scene->GetGameObject();

	for (const auto& g : gameObjects)
	{
		if (g->GetMeshRenderer() == nullptr)
			continue;

		g->GetMeshRenderer()->Render();
	}
}
