//#include "pch.h"
//#include "Mesh.h"
//
//class Grid
//{
//public:
//	Grid() {}
//	std::shared_ptr<Mesh> Init(float width, float depth, UINT m, UINT n)
//	{
//		UINT vertexCount = m * n;
//		UINT faceCount = (m - 1) * (n - 1) * 2;
//
//		float halfWidth = 0.5f * width;
//		float halfDepth = 0.5f * depth;
//
//		float dx = width / (n - 1);
//		float dz = depth / (m - 1);
//
//		vertices.resize(vertexCount);
//
//		for (UINT i = 0; i < m; i++)
//		{
//			float z = halfDepth - i * dz;
//			for (UINT j = 0; j < n; j++)
//			{
//				float x = -halfWidth + j * dx;
//
//				vertices[i * n + j].pos = XMFLOAT3(x, 0.0f, z);
//			}
//		}
//
//		indices.resize(faceCount * 3);
//
//		UINT k = 0;
//		for (UINT i = 0; i < m-1; i++)
//		{
//			for (UINT j = 0; j < n-1; j++)
//			{
//				indices[k] = i * n + j;
//
//				k += 6;
//			}
//		}
//
//
//		
//		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
//		mesh->Init(vertices, indices);
//
//		return mesh;
//	}
//
//public:
//	std::vector<Vertex> vertices;
//	std::vector<uint16_t> indices;
//};