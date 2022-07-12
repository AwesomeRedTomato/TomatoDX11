#include "pch.h"
#include "Graphics.h"
#include "Light.h"
#include "Transform.h"
#include "Imgui/imgui.h"

void Light::Start()
{
	_lightInfo.color.ambient = FLOAT3(1.0f, 1.0f, 1.0f);
}

void Light::FinalUpdate()
{
	_lightInfo.position = GetTransform()->GetWorldPosition();
}

void Light::UpdateImGui()
{
	if (ImGui::Begin(GetGameObject()->GetObjectName().c_str()))
	{
		ImGui::Text("\nLight");
		ImGui::ColorEdit3("Ambient Color", &_lightInfo.color.ambient.x);
		ImGui::ColorEdit3("Diffuse Color", &_lightInfo.color.diffuse.x);
		ImGui::ColorEdit3("Specular Color", &_lightInfo.color.specular.x);

		ImGui::End();
	}
}