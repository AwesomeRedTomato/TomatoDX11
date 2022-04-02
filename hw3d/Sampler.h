#pragma once
class Sampler
{
public:
	void Init();
	void Bind();

protected:
	ComPtr<ID3D11SamplerState> _samplerState;
};

