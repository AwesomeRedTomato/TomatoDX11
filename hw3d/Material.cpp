#include "pch.h"
#include "Material.h"

void Material::Init()
{
	_texture->Init();
	_shader->Init();
	_sampler->Init();
}

void Material::Render()
{
	_shader->Render();
	_sampler->Render();
	_texture->Render();
}

void Material::PushData()
{

}
