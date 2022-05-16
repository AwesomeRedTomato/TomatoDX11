#include "pch.h"
#include "MeshRenderer.h"
#include "Transform.h"

void MeshRenderer::Update()
{
	// Render(); ÀÌ»ç°©´Ï´Ù(camera->Render())
}

void MeshRenderer::Render()
{
	GetTransform()->PushData();
	_material->PushData();
	_mesh->Render();

}
