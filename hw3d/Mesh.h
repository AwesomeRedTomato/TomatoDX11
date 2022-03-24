#pragma once
class Mesh
{
public:
	void Init(vector<Vertex>& vertices, vector<uint16_t>& indices);
	void Bind();

private:
	ComPtr<ID3D11Buffer>	_vertexBuffer;
	ComPtr<ID3D11Buffer>	_indexBuffer;

	UINT					_vertexStride;
	DXGI_FORMAT				_indexFormat;
};

