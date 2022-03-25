//#pragma once
//#include "Graphics.h"
//
//enum class CONSTANT_BUFFER_TYPE
//{
//	VERTEX_CONSTANT,
//	PIXEL_CONSTANT,
//};
//
//template<typename C>
//class ConstantBuffer
//{
//public:
//	ConstantBuffer(CONSTANT_BUFFER_TYPE type);
//	ConstantBuffer(CONSTANT_BUFFER_TYPE type, const C& buffer, UINT size);
//	void Bind(CONSTANT_BUFFER_TYPE type);
//
//public:
//	void Update(const C& consts);
//
//protected:
//	ComPtr<ID3D11Buffer> _cb;
//	CONSTANT_BUFFER_TYPE _cbSize;
//
//	UINT _byteWidth = 0;
//
//};
//
//template<typename C>
//inline ConstantBuffer<C>::ConstantBuffer(CONSTANT_BUFFER_TYPE type)
//{
//	D3D11_BUFFER_DESC cbDesc;
//	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
//	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cbDesc.MiscFlags = 0U;
//	cbDesc.ByteWidth = sizeof(C);
//	cbDesc.StructureByteStride = 0u;
//	DEVICE->CreateBuffer(&cbDesc, nullptr, _cb.GetAddressOf());
//
//	Bind(type);
//}
//
//template<typename C>
//inline ConstantBuffer<C>::ConstantBuffer(CONSTANT_BUFFER_TYPE type, const C& buffer, UINT size)
//{
//	_cbSize = size;
//
//	D3D11_BUFFER_DESC cbDesc;
//	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
//	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	cbDesc.MiscFlags = 0u;
//	cbDesc.ByteWidth = _cbSize;
//	cbDesc.StructureByteStride = 0u;
//	D3D11_SUBRESOURCE_DATA csd = {};
//	csd.pSysMem = &buffer;
//	DEVICE->CreateBuffer(&cbDesc, &csd, _cb.GetAddressOf());
//
//	Bind(type);
//}
//
//template<typename C>
//inline void ConstantBuffer<C>::Bind(CONSTANT_BUFFER_TYPE type)
//{
//	switch (type)
//	{
//	case CONSTANT_BUFFER_TYPE::VERTEX_CONSTANT:
//		CONTEXT->VSSetConstantBuffers(0u, 1u, _cb.GetAddressOf());
//		break;
//
//	case CONSTANT_BUFFER_TYPE::PIXEL_CONSTANT:
//		CONTEXT->PSSetConstantBuffers(0u, 1u, _cb.GetAddressOf());
//		break;
//	default:
//		break;
//	}
//
//
//}
//
//template<typename C>
//inline void ConstantBuffer<C>::Update(const C& consts)
//{
//	D3D11_MAPPED_SUBRESOURCE msr;
//	CONTEXT->Map(_cb.GetAddressOf(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);
//
//	memcpy(msr.pData, &consts, _cbSize);
//	CONTEXT->Unmap(_cb.Get(), 0u);
//}
