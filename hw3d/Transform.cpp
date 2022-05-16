#include "pch.h"
#include "Transform.h"
#include "Graphics.h"
#include "Camera.h"
#include "TomatoMath.h"

void Transform::LateUpdate()
{
	MATRIX matScale = MATRIX::CreateScale(_localScale);
	MATRIX matRotation = MATRIX::CreateRotationX(_localRotation.x);
	matRotation *= MATRIX::CreateRotationY(_localRotation.y);
	matRotation *= MATRIX::CreateRotationZ(_localRotation.z);
	MATRIX matTranslation = MATRIX::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation;
	_matWorld = _matLocal;

	std::shared_ptr<Transform> parent = GetParentTransform().lock();
	if (parent)
	{
		_matWorld *= parent->GetWorldMatrix();
	}
}

void Transform::PushData()
{
	TransformParams transformParam{};
	transformParam.matWorld = _matWorld;
	transformParam.matView = Camera::S_MatView;
	transformParam.matProjection = Camera::S_MatProjection;
	transformParam.matWV = _matWorld * Camera::S_MatView;
	transformParam.matWVP = _matWorld * Camera::S_MatView * Camera::S_MatProjection;

	CONSTANT_BUFFER(CB_TYPE::TRANSFORM)->Init(0u, sizeof(TransformParams), 1u);
	CONSTANT_BUFFER(CB_TYPE::TRANSFORM)->PushData(&transformParam, sizeof(TransformParams));
	CONSTANT_BUFFER(CB_TYPE::TRANSFORM)->Render();
}

