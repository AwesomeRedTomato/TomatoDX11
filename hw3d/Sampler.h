#pragma once
class Sampler
{
public:
	void Init();
	void Render();

protected:
	ComPtr<ID3D11SamplerState> _samplerState;
};

