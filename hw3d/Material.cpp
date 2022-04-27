#include "pch.h"
#include "Material.h"

void Material::Init()
{
	_shader->Init();
	_texture->Init();
	_sampler->Init();
}

void Material::Render()
{
	_shader->Render();
	_texture->Render();
	_sampler->Render();
}