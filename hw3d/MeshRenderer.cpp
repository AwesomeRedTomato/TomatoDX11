#include "pch.h"
#include "MeshRenderer.h"

void MeshRenderer::Update()
{
	Render();
}

void MeshRenderer::Render()
{
	_material->PushData();
	_mesh->Render();
}
