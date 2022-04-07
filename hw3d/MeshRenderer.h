#pragma once
#include "Mesh.h"
#include "Material.h"

class MeshRenderer
{
public:
	void Init();
	void Bind();

public:


private:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;
};

