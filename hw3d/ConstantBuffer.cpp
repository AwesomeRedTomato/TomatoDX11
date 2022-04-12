#include "pch.h"
#include "ConstantBuffer.h"
#include "Graphics.h"

void ConstantBuffer::Init(void* buffer, UINT size)
{
	_elementSize = (size + 255) & ~255;

	memcpy_s(&_buffer, _elementSize, buffer, size);

	D3D11_BUFFER_DESC tDesc;
	tDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tDesc.MiscFlags = 0u;
	tDesc.ByteWidth = size;
	tDesc.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &_buffer;
	DEVICE->CreateBuffer(&tDesc, &csd, &_constantBuffer);

	D3D11_MAPPED_SUBRESOURCE msr;
	CONTEXT->Map(_constantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);

	const Color cb2 =
	{
		{
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f},
		}
	};

	D3D11_BUFFER_DESC cbd2;
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.CPUAccessFlags = 0u;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;
	DEVICE->CreateBuffer(&cbd2, &csd2, &_constantBuffer2);
}

void ConstantBuffer::Bind()
{
	CONTEXT->VSSetConstantBuffers(0u, 1u, _constantBuffer.GetAddressOf());
	CONTEXT->PSSetConstantBuffers(0u, 1u, _constantBuffer2.GetAddressOf());
}
