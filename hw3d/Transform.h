#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform() : Component(COMPONENT_TYPE::TRANSFORM) {}
	virtual ~Transform() = default;
	
public:
	virtual void LateUpdate() override;
	void PushData();

public:
	const FLOAT3& GetLocalPosition() { return _localPosition; }
	const FLOAT3& GetLocalRotation() { return _localRotation; }
	const FLOAT3& GetLocalScale() { return _localScale; }

	MATRIX& GetWorldMatrix() { return _matWorld; }
	FLOAT3 GetWorldPosition() { return _matWorld.Translation(); }


	void SetLocalPosition(const FLOAT3& position) { _localPosition = position; }
	void SetLocalRotation(const FLOAT3& rotation) { _localRotation = rotation; }
	void SetLocalScale(const FLOAT3& scale) { _localScale = scale; }

	void SetParentTransform(std::shared_ptr<Transform> parent) { _parent = parent; }
	std::weak_ptr<Transform> GetParentTransform() { return _parent; }

private:
	FLOAT3 _localPosition = {};
	FLOAT3 _localRotation = {};
	FLOAT3 _localScale = { 1.0f, 1.0f, 1.0f };

	MATRIX _matLocal = {};
	MATRIX _matWorld = {};

	std::weak_ptr<Transform> _parent;
};

