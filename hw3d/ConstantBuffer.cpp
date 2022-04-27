#include "pch.h"
#include "ConstantBuffer.h"
#include "Graphics.h"

void ConstantBuffer::Init(UINT slot, UINT size, UINT count)
{
	_slot = slot;
	_elementSize = (size + 255) & ~255;
	_elementCount = count;
}

void ConstantBuffer::Render()
{
	CONTEXT->VSSetConstantBuffers(_slot, 1u, _constantBuffer.GetAddressOf());
}

void ConstantBuffer::PushData(void* buffer, UINT size)
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
	memcpy_s(msr.pData, bufferSize, buffer, size);
	CONTEXT->Unmap(_constantBuffer.Get(), 0u);
}
