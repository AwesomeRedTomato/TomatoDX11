//#pragma once
//#include "Component.h"
//
//class Transform : public Component
//{
//public:
//	Transform() : Component(COMPONENT_TYPE::TRANSFORM) {}
//	virtual ~Transform() = default;
//	
//public:
//	virtual void Update() override;
//
//public:
//	const XMFLOAT3& GetLocalPosition() { return _localPosition; }
//	const XMFLOAT3& GetLocalRotation() { return _localRotation; }
//	const XMFLOAT3& GetLocalScale() { return _localScale; }
//
//	const XMMATRIX& GetLocalMatrix() { return _matLocal; }
//	const XMMATRIX& GetWorldMatirx() { return _matWorld; }
//
//	void SetLocalPosition(const XMFLOAT3& position) { _localPosition = position; }
//	void SetLocalRotation(const XMFLOAT3& rotation) { _localRotation = rotation; }
//	void SetLocalScale(const XMFLOAT3& scale) { _localScale = scale; }
//
//	void SetParentTransform(std::shared_ptr<Transform> parent) { _parent = parent; }
//	std::weak_ptr<Transform> GetParentTransform() { return _parent; }
//
//private:
//	XMFLOAT3 _localPosition = {};
//	XMFLOAT3 _localRotation = {};
//	XMFLOAT3 _localScale = { 1.0f, 1.0f, 1.0f };
//
//	XMMATRIX _matLocal = {};
//	XMMATRIX _matWorld = {};
//
//	std::weak_ptr<Transform> _parent;
//};
//
