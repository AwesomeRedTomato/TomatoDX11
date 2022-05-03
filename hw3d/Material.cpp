#include "pch.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Graphics.h"

void Material::PushData()
{
	CONSTANT_BUFFER(CB_TYPE::MATERIAL)->PushData(&_params, sizeof(MaterialParams));

	for (UINT i = 0; i < _textures.size(); i++)
	{
		if (_textures[i] == nullptr)
			continue;

		_textures[i]->Render(i);
	}

	_shader->Update();
}
 