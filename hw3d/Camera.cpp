#include "pch.h"
#include "Camera.h"
#include "Graphics.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"
#include "MeshRenderer.h"

MATRIX Camera::S_MatView;
MATRIX Camera::S_MatProjection;


void Camera::LateUpdate()
{
	_matView = GetTransform()->GetWorldMatrix().Invert();

	_matProjection = XMMatrixPerspectiveFovLH(_fov, (3.0f/ 4.0f), _near, _far);
}

void Camera::Render()
{
	S_MatView = _matView;
	S_MatProjection = _matProjection;
}
