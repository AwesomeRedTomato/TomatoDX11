#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Sampler.h"

/* �߰� ����
enum class TEXTURE_TYPE
{
	NORMAL
}
*/

class Material
{
public:
	void Init();
	void Bind();

	std::shared_ptr<Texture> GetTexture() { return _texture; }

	void SetShader(std::shared_ptr<Shader> shader) { _shader = shader; }
	// ���� ����
	// void SetTexture(TEXTURE_TYPE type, std::shared_ptr<Texture> texture)
	void SetTexture(std::shared_ptr<Texture> texture) { _texture = texture; }
	void SetSampler(std::shared_ptr<Sampler> sampler) { _sampler = sampler; }

private:
	std::shared_ptr<Shader> _shader = std::make_shared<Shader>();
	std::shared_ptr<Sampler> _sampler = std::make_shared<Sampler>();

	// ���� ���� std::array<std::shared_ptr<Texture>, TEXTURE_TYPE::END> _textures;
	std::shared_ptr<Texture> _texture = std::make_shared<Texture>();
};

