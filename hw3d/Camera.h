//#pragma once 
//#include "Component.h"
//
//class Camera : public Component
//{
//public:
//	Camera() : Component(COMPONENT_TYPE::CAMERA) {}
//	virtual ~Camera() = default;
//
//public:
//	void Bind();
//	virtual void Update();
//	virtual void Render();
//
//private:
//	float _near = 1.f;
//	float _far = 1000.f;
//	float _fov = XM_PI / 4.f;
//	float _scale = 1.f;
//
//	XMMATRIX _matView = {};
//	XMMATRIX _matProjection = {};
//
//public:
//	static XMMATRIX S_MatView;
//	static XMMATRIX S_MatProjection;
//};
//
