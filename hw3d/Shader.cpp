#include "pch.h"
#include "Shader.h"
#include "Graphics.h"

void Shader::Init()
{
	CreateShader(L"SolidVS.cso", _vsBlob);
	CreateShader(L"SolidPS.cso", _psBlob);

	DEVICE->CreateVertexShader(_vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());
	DEVICE->CreatePixelShader(_psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	DEVICE->CreateSamplerState(&samplerDesc, _samplerState.GetAddressOf());

	D3D11_INPUT_ELEMENT_DESC desc[] =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	DEVICE->CreateInputLayout(desc, std::size(desc), _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
}

void Shader::Update()
{
	CONTEXT->VSSetShader(_vertexShader.Get(), nullptr, 0u);
	CONTEXT->PSSetShader(_pixelShader.Get(), nullptr, 0u);
	CONTEXT->PSSetSamplers(0u, 1u, _samplerState.GetAddressOf());

	CONTEXT->IASetInputLayout(_inputLayout.Get());
}

void Shader::CreateShader(const std::wstring& path, ComPtr<ID3DBlob>& pBlob)
{
	D3DReadFileToBlob(path.c_str(), pBlob.GetAddressOf());
}

ComPtr<ID3DBlob> Shader::GetByteCode()
{
	return _vsBlob;
}
