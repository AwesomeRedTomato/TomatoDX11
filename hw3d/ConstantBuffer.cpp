#include "pch.h"
#include "ConstantBuffer.h"
#include "Graphics.h"

void ConstantBuffer::Init(float angle, int x, int z)
{
	const Transform transform
	{
		 XMMatrixTranspose(
			XMMatrixRotationZ(angle) *
			XMMatrixRotationX(angle) *
			XMMatrixTranslation(x,0.0f,z + 4.0f) *
			XMMatrixPerspectiveLH(1.0f,3.0f / 4.0f,0.5f,10.0f))

	};

	D3D11_BUFFER_DESC tDesc;
	tDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tDesc.MiscFlags = 0u;
	tDesc.ByteWidth = sizeof(transform);
	tDesc.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &transform;
	DEVICE->CreateBuffer(&tDesc, &csd, &_constantBuffer);

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
