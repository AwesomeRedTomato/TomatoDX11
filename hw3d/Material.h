#pragma once

enum class TEXTURE_TYPE
{
	DIFFUSE,
	NORMAL,
	END
};

enum
{
	TEXTURE_COUNT = static_cast<uint8_t>(TEXTURE_TYPE::END),
};

struct MaterialParams
{
	void SetTexOn(UINT index, UINT value) { texOnParams[index] = value; }

	std::array<UINT, TEXTURE_COUNT> texOnParams;
};

class Shader;
class Texture;
class Material
{
public:
	void PushData();

public:
	std::shared_ptr<Shader> GetShader() { return _shader; }

public:
	void SetShader(std::shared_ptr<Shader> shader) { _shader = shader; }
	void SetTexture(TEXTURE_TYPE type, std::shared_ptr<Texture> texture) { _textures[static_cast<UINT>(type)] = texture; }

private:
	MaterialParams										_params;
	std::shared_ptr<Shader>								_shader;
	std::array<std::shared_ptr<Texture>, TEXTURE_COUNT> _textures;
};

