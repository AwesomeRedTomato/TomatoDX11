#include "pch.h"
#include "Transform.h"
#include "Graphics.h"
#include "Camera.h"

void Transform::FinalUpdate()
{
	MATRIX matScale = MATRIX::CreateScale(_localScale);
	MATRIX matRotation = MATRIX::CreateRotationX(_localRotation.x);
	matRotation *= MATRIX::CreateRotationY(_localRotation.y);
	matRotation *= MATRIX::CreateRotationZ(_localRotation.z);
	MATRIX matTranslation = MATRIX::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation;
	_matWorld = _matLocal;

	std::shared_ptr<Transform> parent = GetParent().lock();
	if (parent != nullptr)
	{
		_matWorld *= parent->GetWorldMatrix();
	}
}

void Transform::UpdateImGui()
{
	if (!GetGameObject()->GetObjectName().empty())
	{
		if (ImGui::Begin(GetGameObject()->GetObjectName().c_str()))
		{
			ImGui::Text("Transform");
			ImGui::SliderFloat3("Position", &_localPosition.x, -10.0f, 100.0f);
			ImGui::SliderFloat3("Rotation", &_localRotation.x, -180.0f, 180.0f);
			ImGui::SliderFloat3("Scale", &_localScale.x, 0.0f, 1.0f);

			if(ImGui::Button("Reset"))
			{
				GetTransform()->SetLocalScale(FLOAT3(1.0f, 1.0f, 1.0f));
				GetTransform()->SetLocalPosition(FLOAT3(0, 0, 0));
				GetTransform()->SetLocalRotation(FLOAT3(0, 0, 0));
			}
		}
		ImGui::End();
	}
}

void Transform::PushData()
{
	TRANSFORM_PARAMS transformParams = {};
	transformParams.matWorld = _matWorld;
	transformParams.matView = Camera::S_MatView;
	transformParams.matProjection = Camera::S_MatProjection;
	transformParams.matWV = _matWorld * Camera::S_MatView;
	transformParams.matWVP = _matWorld * Camera::S_MatView * Camera::S_MatProjection;

	CONSTANT_BUFFER(CB_TYPE::TRANSFORM)->Init(static_cast<UINT>(CB_TYPE::TRANSFORM), sizeof(TRANSFORM_PARAMS), 1u);
	CONSTANT_BUFFER(CB_TYPE::TRANSFORM)->PushVertexConstant(&transformParams);
}

