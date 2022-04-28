#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Sampler.h"

class Material
{
public:
	void Init();
	void Render();

	void PushData();

public:
	std::shared_ptr<Texture> GetTexture() { return _texture; }

public:
	void SetShader(std::shared_ptr<Shader> shader) { _shader = shader; }
	void SetTexture(std::shared_ptr<Texture> texture) { _texture = texture; }
	void SetSampler(std::shared_ptr<Sampler> sampler) { _sampler = sampler; }

private:
	std::shared_ptr<Shader> _shader = std::make_shared<Shader>();
	std::shared_ptr<Sampler> _sampler = std::make_shared<Sampler>();
	std::shared_ptr<Texture> _texture = std::make_shared<Texture>();
};

