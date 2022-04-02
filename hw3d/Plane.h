#pragma once
#include "pch.h"
#include "Mesh.h"

class Plane
{
public:
	std::shared_ptr<Mesh> Init()
	{
		vertices.emplace_back(Vertex(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)));
		vertices.emplace_back(Vertex(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)));

		indices.emplace_back(0);
		indices.emplace_back(3);
		indices.emplace_back(1);
		indices.emplace_back(0);
		indices.emplace_back(2);
		indices.emplace_back(3);

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->Init(vertices, indices);

		return mesh;
	}

public:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};