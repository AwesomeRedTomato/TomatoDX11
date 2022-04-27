#pragma once
#include "Mesh.h"
#include "Material.h"

class MeshRenderer
{
public:
	void Init();
	void Render();

public:
	void SetMesh(std::shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(std::shared_ptr<Material> material) { _material = material; }

private:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;
};

