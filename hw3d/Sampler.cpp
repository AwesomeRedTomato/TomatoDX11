#include "pch.h"
#include "Sampler.h"
#include "Graphics.h"

void Sampler::Init()
{
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	DEVICE->CreateSamplerState(&samplerDesc, _samplerState.GetAddressOf());
}

void Sampler::Render()
{
	CONTEXT->PSSetSamplers(0u, 1u, _samplerState.GetAddressOf());
}
