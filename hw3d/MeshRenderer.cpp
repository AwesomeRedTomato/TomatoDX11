#include "pch.h"
#include "MeshRenderer.h"
#include "Transform.h"

void MeshRenderer::Update()
{
}

void MeshRenderer::Render()
{
	GetTransform()->PushData();
	_material->PushData();
	_mesh->Render();
}
