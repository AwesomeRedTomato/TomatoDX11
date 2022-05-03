#include "pch.h"
#include "MeshRenderer.h"

void MeshRenderer::Init()
{
}

void MeshRenderer::Render()
{
	_material->PushData();
	_mesh->Render();
}
