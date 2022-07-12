#include "pch.h"
#include "ConstantBuffer.h"
#include "Graphics.h"

void ConstantBuffer::Init(UINT slot, UINT size, UINT count)
{
	_slot = slot;
	_elementSize = (size + 255) & ~255;
	_elementCount = count;
}

void ConstantBuffer::PushVertexConstant(void* buffer)
{
	UINT bufferSize = _elementSize * _elementCount;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0u;
	cbDesc.ByteWidth = bufferSize;
	cbDesc.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &buffer;
	DEVICE->CreateBuffer(&cbDesc, &csd, &_constantBuffer);

	D3D11_MAPPED_SUBRESOURCE msr;
	CONTEXT->Map(_constantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);
	memcpy_s(msr.pData, bufferSize, buffer, _elementSize);
	CONTEXT->Unmap(_constantBuffer.Get(), 0u);
	
	CONTEXT->VSSetConstantBuffers(_slot, _elementCount, _constantBuffer.GetAddressOf());
}

void ConstantBuffer::PushPixelConstant(void* buffer)
{
	UINT bufferSize = _elementSize * _elementCount;
	
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0u;
	cbDesc.ByteWidth = bufferSize;
	cbDesc.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &buffer;
	DEVICE->CreateBuffer(&cbDesc, &csd, &_constantBuffer);

	D3D11_MAPPED_SUBRESOURCE msr;
	CONTEXT->Map(_constantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);
	memcpy_s(msr.pData, bufferSize, buffer, _elementSize);
	CONTEXT->Unmap(_constantBuffer.Get(), 0u);

	CONTEXT->PSSetConstantBuffers(_slot, _elementCount, _constantBuffer.GetAddressOf());
}
