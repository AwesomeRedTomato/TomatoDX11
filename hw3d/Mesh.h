#pragma once
class Mesh
{
public:
	void Init(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);
	void Render();

	UINT GetIndexCount() { return _indexCount; }

protected:
	ComPtr<ID3D11Buffer>	_vertexBuffer;
	ComPtr<ID3D11Buffer>	_indexBuffer;

	UINT					_vbStride;
	UINT					_vbOffset;

	DXGI_FORMAT				_indexFormat;
	UINT					_ibOffset;
	UINT					_indexCount;
};

