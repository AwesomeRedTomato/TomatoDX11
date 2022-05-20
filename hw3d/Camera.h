#pragma once
#include "Component.h"

// 구현 예정
enum class PERSPECTIVE_TYPE
{
	PERSPECTIVE,
	OTHOGRAPHIC,
};

class Camera : public Component
{
public:
	Camera() : Component(COMPONENT_TYPE::CAMERA) {}
	virtual ~Camera() {}

public:
	virtual void FinalUpdate() override;

	void Render();

public:
	float _near = 1.0f;
	float _far = 1000.f;
	float _fov = XM_PI / 4.0f;
	float _scale = 1.0f;

	MATRIX _matView = {};
	MATRIX _matProjection = {};

	static MATRIX S_MatView;
	static MATRIX S_MatProjection;
};