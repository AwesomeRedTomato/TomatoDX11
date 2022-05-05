#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"

class MeshRenderer : public Component
{
public:
	MeshRenderer() : Component(COMPONENT_TYPE::MESH_RENDERER) {}
	virtual ~MeshRenderer() {}

public:
	void Update() override;

	void Render();

public:
	void SetMesh(std::shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(std::shared_ptr<Material> material) { _material = material; }

private:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;
};