#include "pch.h"
#include "Mesh.h"

class Cube
{
public:
	Cube() {}
	std::shared_ptr<Mesh> Init()
	{
		vertices.emplace_back(Vertex(XMFLOAT3(-1.0f, -1.0f, -1.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(1.0f, -1.0f, -1.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(-1.0f, 1.0f, -1.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(1.0f, 1.0f, -1.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(-1.0f, -1.0f, 1.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(1.0f, -1.0f, 1.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(-1.0f, 1.0f, 1.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f)));

		// ¾Õ¸é
		indices.emplace_back(0); 
		indices.emplace_back(2); 
		indices.emplace_back(1);
		indices.emplace_back(2); 
		indices.emplace_back(3); 
		indices.emplace_back(1);

		// µÞ¸é
		indices.emplace_back(1); 
		indices.emplace_back(3); 
		indices.emplace_back(5);
		indices.emplace_back(3); 
		indices.emplace_back(7);
		indices.emplace_back(5);

		// À­¸é
		indices.emplace_back(2); 
		indices.emplace_back(6); 
		indices.emplace_back(3);
		indices.emplace_back(3); 
		indices.emplace_back(6); 
		indices.emplace_back(7);

		// ¾Æ·§¸é
		indices.emplace_back(4); 
		indices.emplace_back(5); 
		indices.emplace_back(7);
		indices.emplace_back(4); 
		indices.emplace_back(7);
		indices.emplace_back(6);

		// ¿ÞÂÊ¸é
		indices.emplace_back(0); 
		indices.emplace_back(4); 
		indices.emplace_back(2);
		indices.emplace_back(2); 
		indices.emplace_back(4); 
		indices.emplace_back(6);

		// ¿À¸¥ÂÊ¸é
		indices.emplace_back(0); 
		indices.emplace_back(1); 
		indices.emplace_back(4);
		indices.emplace_back(1); 
		indices.emplace_back(5); 
		indices.emplace_back(4);

		std::shared_ptr<Mesh> mesh = std::make_unique<Mesh>();
		mesh->Init(vertices, indices);

		return mesh;
	}

public:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};