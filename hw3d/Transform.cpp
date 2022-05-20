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

void Transform::UpdateImGui()
{
	static float scale[3]	 = { _localScale.x, _localScale.y, _localScale.z };
	static float position[3] = { _localPosition.x, _localPosition.y, _localPosition.z };
	static float rotation[3] = { _localRotation.x, _localRotation.y, _localRotation.z };
	
	if (!GetGameObject()->GetObjectName().empty())
	{
		if (ImGui::Begin(GetGameObject()->GetObjectName().c_str()))
		{
			ImGui::SliderFloat3("Position", position, 0.0f, 100.0f);
			ImGui::SliderFloat3("Rotation", rotation, 0.0f, 100.0f);
			ImGui::SliderFloat3("Scale", scale, 0.0f, 100.0f);
		}
		ImGui::End();
	}
}

void Transform::PushData()
{
	TransformParams transformParam{};
	transformParam.matView = Camera::S_MatView;
	transformParam.matViewProjection = Camera::S_MatView * Camera::S_MatProjection;

	CONSTANT_BUFFER(CB_TYPE::TRANSFORM)->Init(static_cast<UINT>(CB_TYPE::TRANSFORM), sizeof(TransformParams), 1u);
	CONSTANT_BUFFER(CB_TYPE::TRANSFORM)->PushData(&transformParam, sizeof(TransformParams));
	CONSTANT_BUFFER(CB_TYPE::TRANSFORM)->Render();
}

