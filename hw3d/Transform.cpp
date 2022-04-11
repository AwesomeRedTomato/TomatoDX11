#include "pch.h"
#include "Transform.h"

void Transform::Update()
{
	XMMATRIX matScale = XMMatrixScaling(_localScale.x, _localScale.y, _localScale.z);
	XMMATRIX matRotation = XMMatrixRotationX(_localRotation.x) * 
		XMMatrixRotationY(_localRotation.y) *
		XMMatrixRotationZ(_localRotation.z);
	XMMATRIX matTranslation = XMMatrixTranslation(_localPosition.x, _localPosition.y, _localPosition.z);

	_matLocal = matScale * matRotation * matTranslation;
	_matWorld = _matLocal;

	std::shared_ptr<Transform> parent = GetParentTransform().lock();
	if (parent != nullptr)
	{
		_matWorld *= parent->GetWorldMatirx();
	}
}
