#include "pch.h"
#include "Shader.h"
#include "Graphics.h"

void Shader::Init()
{
	CreateShader(L"VertexShader.cso", _vsBlob);
	CreateShader(L"PixelShader.cso", _psBlob);

	DEVICE->CreateVertexShader(_vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());
	DEVICE->CreatePixelShader(_psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());

	D3D11_INPUT_ELEMENT_DESC desc[] =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	DEVICE->CreateInputLayout(desc, size(desc), _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
}

void Shader::Bind()
{
	CONTEXT->VSSetShader(_vertexShader.Get(), nullptr, 0u);
	CONTEXT->PSSetShader(_pixelShader.Get(), nullptr, 0u);

	CONTEXT->IASetInputLayout(_inputLayout.Get());
}

void Shader::CreateShader(const wstring& path, ComPtr<ID3DBlob>& pBlob)
{
	D3DReadFileToBlob(path.c_str(), pBlob.GetAddressOf());
}

ComPtr<ID3DBlob> Shader::GetByteCode()
{
	return _vsBlob;
}
