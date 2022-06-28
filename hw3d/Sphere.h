#pragma once
#include "pch.h"
#include "Mesh.h"

class Sphere
{
public:
	std::shared_ptr<Mesh> Init()
	{
		
	}

public:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};