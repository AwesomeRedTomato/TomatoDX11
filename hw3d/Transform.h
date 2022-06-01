#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform() : Component(COMPONENT_TYPE::TRANSFORM) {};
	virtual ~Transform() = default;

public:
	virtual void FinalUpdate() override;
	virtual void UpdateImGui() override;
	void PushData();

public:
	const FLOAT3& GetLocalPosition() { return _localPosition; }
	const FLOAT3& GetLocalRotation() { return _localRotation; }
	const FLOAT3& GetLocalScale() { return _localScale; }

	const MATRIX& GetWorldMatrix() { return _matWorld; }
	FLOAT3 GetWorldPosition() { return _matWorld.Translation(); }

	FLOAT3 GetRight() { return _matWorld.Right(); }
	FLOAT3 GetUp() { return _matWorld.Up(); }
	FLOAT3 GetLook() { return _matWorld.Backward(); }

	void SetLocalPosition(const FLOAT3& position) { _localPosition = position; }
	void SetLocalRotation(const FLOAT3& rotation) { _localRotation = rotation; }
	void SetLocalScale(const FLOAT3& scale) { _localScale = scale; }

public:
	void SetParent(std::shared_ptr<Transform> parent) { _parent = parent; }
	std::weak_ptr<Transform> GetParent() { return _parent; }

private:
	// Parent ±‚¡ÿ
	FLOAT3 _localPosition = {};
	FLOAT3 _localRotation = {};
	FLOAT3 _localScale = { 1.f, 1.f, 1.f };

	MATRIX _matLocal = {};
	MATRIX _matWorld = {};

	std::weak_ptr<Transform> _parent;
};

