#include "pch.h"
#include "Transform.h"
#include "Graphics.h"
#include "Camera.h"
// #include "TomatoMath.h"

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
	float scale[3]	 = { _localScale.x, _localScale.y, _localScale.z };
	float rotation[3] = { _localRotation.x, _localRotation.y, _localRotation.z };
	float position[3] = { _localPosition.x, _localPosition.y, _localPosition.z };
	
	if (!GetGameObject()->GetObjectName().empty())
	{
		if (ImGui::Begin(GetGameObject()->GetObjectName().c_str()))
		{
			ImGui::Text("Transform");
			ImGui::SliderFloat3("Position", position, -10.0f, 100.0f);
			ImGui::SliderFloat3("Rotation", rotation, -180.0f, 180.0f);
			ImGui::SliderFloat3("Scale", scale, 0.0f, 1.0f);

			GetTransform()->SetLocalScale(FLOAT3(scale[0], scale[1], scale[2]));
			GetTransform()->SetLocalPosition(FLOAT3(position[0], position[1], position[2]));
			GetTransform()->SetLocalRotation(FLOAT3(rotation[0], rotation[1], rotation[2]));

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
	CONSTANT_BUFFER(CB_TYPE::TRANSFORM)->PushData(&transformParams);
}

