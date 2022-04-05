#include "pch.h"
#include "Material.h"

void Material::Init()
{
	_shader->Init();
	_texture->Init();
	_sampler->Init();
}

void Material::Bind()
{
	_shader->Bind();
	_texture->Bind();
	_sampler->Bind();
}