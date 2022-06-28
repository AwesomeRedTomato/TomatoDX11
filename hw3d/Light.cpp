#include "pch.h"
#include "Graphics.h"
#include "Light.h"
#include "Transform.h"
#include "Imgui/imgui.h"

Light::Light()
	:
	Component(COMPONENT_TYPE::LIGHT)
{
	_lightParams.lightPosition = FLOAT3(0.0f, 0.0f, 0.0f);
	_lightParams.ambientColor = FLOAT3(0.0f, 0.0f, 0.0f);
	_lightParams.diffuseColor = FLOAT3(255.0f, 255.0f, 255.0f);
	_lightParams.specularColor = FLOAT3(0.0f, 0.0f, 0.0f);
	_lightParams.lightType = (UINT)LIGHT_TYPE::POINT_LIGHT;
	_lightParams.intensity = 1.0f;
	_lightParams.range = 1.0f;
}

void Light::FinalUpdate()
{
	_lightParams.lightPosition = GetTransform()->GetWorldPosition();
}

void Light::UpdateImGui()
{
	if (ImGui::Begin(GetGameObject()->GetObjectName().c_str()))
	{
		ImGui::Text("\nLight");
		ImGui::ColorEdit3("Ambient Color", &_lightParams.ambientColor.x);
		ImGui::ColorEdit3("Diffuse Color", &_lightParams.diffuseColor.x);
		ImGui::ColorEdit3("Specular Color", &_lightParams.specularColor.x);

		ImGui::SliderFloat("Intensity", &_lightParams.intensity, 0.0f, 1.0f);
		
		if (_lightParams.lightType == (UINT)LIGHT_TYPE::POINT_LIGHT)
			ImGui::SliderFloat("Range", &_lightParams.range, 0.0f, 10.0f);

		ImGui::End();
	}
}

void Light::PushData()
{
	CONSTANT_BUFFER(CB_TYPE::LIGHT)->Init(static_cast<UINT>(CB_TYPE::LIGHT), sizeof(LIGHT_PARAMS), 1u);
	CONSTANT_BUFFER(CB_TYPE::LIGHT)->PushData(&_lightParams);
}

