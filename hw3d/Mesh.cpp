#include "pch.h"
#include "Mesh.h"
#include "Graphics.h"

void Mesh::Init(vector<Vertex>& vertices, vector<uint16_t>& indices)
{
	_vertexStride = sizeof(Vertex);
	_indexFormat = DXGI_FORMAT_R16_UINT;

	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;
	vbDesc.CPUAccessFlags = 0u;
	vbDesc.MiscFlags = 0u;
	vbDesc.ByteWidth = UINT(sizeof(Vertex) * vertices.size());
	vbDesc.StructureByteStride = _vertexStride;
	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem = vertices.data();
	DEVICE->CreateBuffer(&vbDesc, &vsd, _vertexBuffer.GetAddressOf());

	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.CPUAccessFlags = 0u;
	ibDesc.MiscFlags = 0u;
	ibDesc.ByteWidth = UINT(sizeof(unsigned short) * indices.size());
	ibDesc.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();
	DEVICE->CreateBuffer(&ibDesc, &isd, _indexBuffer.GetAddressOf());
}

void Mesh::Bind()
{
	CONTEXT->IASetVertexBuffers(0u, 1u, _vertexBuffer.GetAddressOf(), &_vertexStride, 0u);
	CONTEXT->IASetIndexBuffer(_indexBuffer.Get(), _indexFormat, 0u);
}
