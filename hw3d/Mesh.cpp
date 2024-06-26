#include "pch.h"
#include "Mesh.h"
#include "Graphics.h"

void Mesh::Init(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
{
	_vbStride = sizeof(Vertex);
	_vbOffset = 0u;
	_indexFormat = DXGI_FORMAT_R16_UINT;
	_ibOffset = 0u;
	_indexCount = indices.size();

	/********** Vertex Buffer **********/
	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;
	vbDesc.CPUAccessFlags = 0u;
	vbDesc.MiscFlags = 0u;
	vbDesc.ByteWidth = sizeof(Vertex) * vertices.size();
	vbDesc.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem = vertices.data();
	DEVICE->CreateBuffer(&vbDesc, &vsd, &_vertexBuffer);

	/********** Index Buffer **********/
	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.CPUAccessFlags = 0u;
	ibDesc.MiscFlags = 0u;
	ibDesc.ByteWidth = sizeof(uint16_t) * indices.size();
	ibDesc.StructureByteStride = sizeof(uint16_t);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();
	DEVICE->CreateBuffer(&ibDesc, &isd, _indexBuffer.GetAddressOf());
}

void Mesh::Render()
{
	CONTEXT->IASetVertexBuffers(0u, 1u, _vertexBuffer.GetAddressOf(), &_vbStride, &_vbOffset);
	CONTEXT->IASetIndexBuffer(_indexBuffer.Get(), _indexFormat, 0u);

	CONTEXT->DrawIndexedInstanced(_indexCount,1u, 0u, 0u, 0u);
}
